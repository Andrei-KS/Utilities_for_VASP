#! /bin/bash

# VASP mpirun configuration
VaspDirect=/home/master/bin/vasp.5.4.4/bin
VaspSTD=$VaspDirect/vasp_std

NumberCore=30


nameSystem=`cat SourceFile_K_E/POSCAR | head -1`
#echo $nameSystem
countAtoms=`cat SourceFile_K_E/POSCAR | awk '(NR == 7){total = 0; for(i = 1; i<NF+1;i++){total += $i}} END {print total}' `
#echo $countAtoms

# VASP search k_Ecut configuration
GGA_Functional="PE PS"
# ="PE PS"
# PE - PBE
# PS - PBEsol

accuracyEtotal=0.001 #eV per atom Convergence
workDirectori="./"
startKpoints=30
startEcutoff=50
startStepEcutoff=25
sFolder="SourceFile_K_E"
setKp="[xy]"
numCore_INCAR=6

windowMeasur=5

#
# Using variable block
#

currKpoints=$startKpoints
currEcutoff=$startEcutoff
currStepEcutoff=$startStepEcutoff

#
# End Using variable block
#


#
# Using function block
#

# is_convergence read data file - "dataConvergence"
function is_convergence {
    if [ -f "dataConvergence" ]
    then
        local listData=`cat dataConvergence | tail -$windowMeasur | awk -v divV=$countAtoms '{printf "%.6f ", $2/divV}'` # get list Value Etotal per atom
        echo $listData
        local upBound=`echo $listData | awk -v acr=$accuracyEtotal '{printf "%.6f", $1+acr}'`
        local downBound=$(echo "scale=6; $upBound - 2*$accuracyEtotal" | bc)

        local indexV=$windowMeasur
        while [ $indexV -gt 1 ]
        do
            local currV=`echo $listData | awk -v i=$indexV '{print $i}'`
            if (( $( echo "$currV > $upBound" | bc -l ) )) || (($( echo "$currV < $downBound" | bc -l ) ))
            then
                return 0
            fi
            indexV=$[ $indexV - 1 ]
        done
    else
        echo "file dataConvergence is not found"
        return 0
    fi
    return 1
}

# getNewValue $1
# $1 - name directory
# $2 - string for sed
# $3 - name target file
function getNewValue {
    mkdir $1
    cp INCAR KPOINTS POSCAR POTCAR ./$1

    cd $1
    sed -i "$2" $3

    mpirun -np $NumberCore $VaspSTD >> _LOGFILE
    awk '/free  energy   TOTEN/{a=1;Etotal=$5} a && /energy  without entropy/{E_entropy=$4; Esigma_0=$7;c=1} c{a=0;c=0} END{print Etotal, "\t", E_entropy, "\t", Esigma_0}' OUTCAR >> ../dataConvergence

    #local ETotal=`bash ../getValueScript.sh $1`
    #echo -e "ETotal $ETotal"
    #echo -e "$1\t$ETotal" >> ../dataConvergence

    cd ..
}

# creatStepSearchEcutoff $1 $2
# $1 - number step
# $2 - functional PE, PS etc.
function creatStepSearchEcutoff {
    workDirectori="$1_step_search_Ecutoff_for_$2"
    echo $workDirectori
    pwd
    mkdir $workDirectori
    cp $sFolder/INCAR $sFolder/KPOINTS $sFolder/POSCAR $sFolder/POTCAR ./$workDirectori
    cd $workDirectori

    rm dataConvergence

    sed -i "s/_myNameSystem/$nameSystem/" KPOINTS
    sed -i "s/_myK$setKp/$currKpoints/g;s/_myK[xyz]/1/g" KPOINTS

    sed -i "s/_myNameSystem/$nameSystem/" INCAR
    sed -i "s/_myGGA/$2/" INCAR
    sed -i "s/_myCore/$numCore_INCAR/" INCAR

    for (( i=$currEcutoff; i < $currEcutoff + $currStepEcutoff * $windowMeasur; i += $currStepEcutoff ))
    do
        getNewValue $i "s/_myEcut/$i/" INCAR
    done

    currEcutoff=$(( $currEcutoff + $currStepEcutoff * ( $windowMeasur - 1 ) ))
    is_convergence
    while [ $? -eq 0 ]
    do
        currEcutoff=$(( $currEcutoff + $currStepEcutoff ))
        echo $currEcutoff
        getNewValue $currEcutoff "s/_myEcut/$currEcutoff/" INCAR
        is_convergence
    done
    currEcutoff=$(( $currEcutoff - $currStepEcutoff * ( $windowMeasur - 1 ) ))
    echo currEcutoff $currEcutoff
    #is_convergence
    #echo end

    cd ..
}

# creatStepSearchKpoints $1 $2
# $1 - number step
# $2 - functional PE, PS etc.
# $3 - k-mesh. exmpl: x, xy, xz, xyz etc.
function creatStepSearchKpoints {
    workDirectori="$1_step_search_Kpoints_for_$2"
    local setK="["$3"]"
    echo $workDirectori
    pwd
    mkdir $workDirectori
    cp $sFolder/INCAR $sFolder/KPOINTS $sFolder/POSCAR $sFolder/POTCAR ./$workDirectori
    cd $workDirectori

    rm dataConvergence

    sed -i "s/_myNameSystem/$nameSystem/" INCAR
    sed -i "s/_myGGA/$2/" INCAR
    sed -i "s/_myCore/$numCore_INCAR/" INCAR
    sed -i "s/_myEcut/$currEcutoff/" INCAR

    sed -i "s/_myNameSystem/$nameSystem/" KPOINTS
    #sed -i "s/_myK$setKp/$currKpoints/g;s/_myK[xyz]/1/g" KPOINTS

    for (( i=1; i < 1 + $windowMeasur; i++ ))
    do
        getNewValue $i "s/_myK$setK/$i/g;s/_myK[xyz]/1/g" KPOINTS
    done

    currKpoints=$(( 1 + $windowMeasur - 1 ) )
    is_convergence
    while [ $? -eq 0 ]
    do
        currKpoints=$(( $currKpoints + 1 ))
        echo $currKpoints
        getNewValue $currKpoints "s/_myK$setK/$currKpoints/g;s/_myK[xyz]/1/g" KPOINTS
        is_convergence
    done
    currKpoints=$(( $currKpoints - $windowMeasur + 1 ))
    echo currKpoints $currKpoints
    cd ..
}

#
#end Using function block
#

#
#main block
#
for i_functional in $GGA_Functional
do
    currKpoints=$startKpoints
    currEcutoff=$startEcutoff
    currStepEcutoff=$startStepEcutoff
    for i_step in 1 2 3
    do
        echo $i_functional $i_step
        creatStepSearchEcutoff $i_step $i_functional
        creatStepSearchKpoints $i_step $i_functional xy
        echo $currEcutoff
        echo $currKpoints

    done
done
pwd

