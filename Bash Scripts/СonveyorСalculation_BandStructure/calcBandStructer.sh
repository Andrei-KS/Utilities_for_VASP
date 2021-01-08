#! /bin/bash
#$1 - SourceFolder
#$2 - choose vasp (STD, GAM, NCL)
#$3 - flagTest
SourceFolder=$1
chooseVasp=$2
flagTest=$3


#relax
setKp_relax="xy"
numKp_relax=25

#DOS
numBAND=250

#BandStructure


currDir=$PWD

#
# VASP mpirun configuration
VaspDirect=/home/master/bin/vasp.5.4.4/bin
VaspSTD=$VaspDirect/vasp_std
VaspNCL=$VaspDirect/vasp_ncl
VaspGAM=$VaspDirect/vasp_gam

currVASP=$VaspSTD
NumberCore=30

#
# check valid Source Folder
if [ -d "$SourceFolder" ]
then
    #echo "$SourceFolder/INCAR.bs"
    if ( [ -f "$SourceFolder/INCAR.bs" ] \
             && [ -f "$SourceFolder/INCAR.dos" ] \
             && [ -f "$SourceFolder/INCAR.relax" ] \
             && [ -f "$SourceFolder/KPOINTS.bs" ] \
             && [ -f "$SourceFolder/KPOINTS.relax" ] \
             && [ -f "$SourceFolder/POSCAR" ] \
             && [ -f "$SourceFolder/POTCAR" ] )
    then
        echo "SourceFolder=$SourceFolder is correct"
        cd "$SourceFolder"
        SourceFolder=$PWD
        cd "$currDir"
    else
        echo "Not found file in $SourceFolder: INCAR.bs, INCAR.relax, INCAR.dos, RPOINTS.bs, KPOINTS.relax, POSCAR, POTCAR"
        exit 1
    fi
else
    echo "Not found SourceFolder"
    exit 1
fi

#
# choose vasp (STD, GAM, NCL)
if [ -n "$chooseVasp" ]
then
    if [ "$chooseVasp" == "STD" ]
    then
        currVASP=$VaspSTD
    else
        if [ "$chooseVasp" == "NCL" ]
        then
            currVASP=$VaspNCL
        else
            if [ "$chooseVasp" == "GAM" ]
            then
                currVASP=$VaspGAM
            else
                echo "invalid 3 argument: $$chooseVasp"
                exit 1
            fi
        fi
    fi
else
    echo "default: vasp_std"
fi


#
# flafTest
if( [ -n "flagTest" ] )
then
    echo "Test: VASP is not run"
else
    flagTest=0
fi


#
#
nameSystem=`cat POSCAR | head -1 | sed 's/\\r//'`
echo $nameSystem

SourceFilesFolder=$SourceFolder
TargetFolder=./

#internal variables
#this variables do not touch
flagCurrectWorck=1;
nameFolderDOS="DOS"
nameFolderBS="Ek"

# $1 have name who call this runVASP
function runVASP {
    local nameFunction=$1
    if [ $flagTest -eq 0 ]
    then
        mpirun -np $NumberCore $currVASP >> _LOGFILE
        if [ $? -eq 0 ]
        then
            echo "$nameFunction : VASP : Successfully created files in $(pwd)"
            echo "VASP:SuccessfullyS" >> _LOGFALE
        else
            echo "$nameFunction : VASP : ERROR, pleas look at file _LOGFILE in $(pwd)"
            flagCurrectWorck=0;
            exit 1;
        fi
    else
        echo -e "Test_run_VASP -np $NumberCore $currVASP >> _LOGFILE"
    fi
}

function workIsCorrect {
    if [ $flagCurrectWorck -ne 1 ]
    then
        echo "End program, work is not done"
        exit 1;
    fi
}

function relaxStructure {
    workIsCorrect
    if ( [ -f "$SourceFilesFolder/INCAR.relax" ] && [ -f "$SourceFilesFolder/KPOINTS.relax" ] )
    then
        echo "start relax"
        cp "$SourceFilesFolder"/INCAR.relax "$TargetFolder"/INCAR
        cp "$SourceFilesFolder"/KPOINTS.relax "$TargetFolder"/KPOINTS

        cd "$TargetFolder"
        sed -i "s/_myNameSystem/$nameSystem/" KPOINTS
        sed -i "s/_myK[$setKp_relax]/$numKp_relax/g;s/_myK[xyz]/1/g" KPOINTS

        sed -i "s/_myNameSystem/$nameSystem/" INCAR

        runVASP relaxStructure
    else
        echo "relaxStructure : ERROR : not founded INCAR.relax or KPOINTS.relax"
    fi
}

function calcDOS {
    workIsCorrect
    if ( [ -f "$SourceFilesFolder/INCAR.dos" ] )
    then
        echo "start calc DOS"

        if [ -n "$numBAND" ]
        then
            nameFolderDOS=$nameFolderDOS"_NBANDS_"$numBAND
        fi

        mkdir "$nameFolderDOS"

        cp "$SourceFilesFolder"/INCAR.dos "$TargetFolder"/"$nameFolderDOS"/INCAR
        cp "$TargetFolder"/CONTCAR "$TargetFolder"/"$nameFolderDOS"/POSCAR
        cp "$TargetFolder"/KPOINTS "$TargetFolder"/POTCAR "$TargetFolder"/"$nameFolderDOS"/


        cd "$nameFolderDOS"
        sed -i "s/_myNameSystem/$nameSystem/" INCAR
        if [ -n "$numBAND" ]
        then
           echo -e "NBANDS = $numBAND" >> INCAR
        fi

        runVASP calcDOS
        cd ../

    else
        echo "relaxStructure : ERROR : not founded INCAR.dos in $SourceFilesFolder"
    fi
}

function calcBS {
    workIsCorrect
    if ( [ -f "$SourceFilesFolder/INCAR.bs" ] && [ -f "$SourceFilesFolder/KPOINTS.bs" ] )
    then
        echo "start calc BS"

        local PointsBSIsCalculated=`awk '/_myNameSystem/{a=$2} END{print a}' $SourceFilesFolder/KPOINTS.bs | sed 's/\\r//'`

        if [ -n "$PointsBSIsCalculated" ]
        then
            nameFolderBS=$nameFolderBS"_"$PointsBSIsCalculated
        fi

        if [ -n "$numBAND" ]
        then
            nameFolderBS=$nameFolderBS"_NBANDS_"$numBAND
        fi

        mkdir $nameFolderBS
        echo -e "\n"$PWD

        cp "$nameFolderDOS"/* "$TargetFolder"/"$nameFolderBS"/
        cp "$SourceFilesFolder"/INCAR.bs "$TargetFolder"/"$nameFolderBS"/INCAR
        cp "$SourceFilesFolder"/KPOINTS.bs "$TargetFolder"/"$nameFolderBS"/KPOINTS

        cd "$nameFolderBS"
        sed -i "s/_myNameSystem/$nameSystem/" INCAR
        if [ -n "$numBAND" ]
        then
            echo -e "NBANDS = $numBAND" >> INCAR
        fi

        sed -i "s/_myNameSystem/$nameSystem/" KPOINTS

        runVASP calcBS
        cd ../

    else
        echo "calcBS : ERROR : not founded INCAR.bs or KPOINTS.bs in $SourceFilesFolder"
    fi
}

echo "Start program"
if ( [ -f "POSCAR" ] && [ -f "POTCAR" ] )
then
    relaxStructure
    calcDOS
    calcBS
else
    echo "ERROR : not founded POSCAR and POTCAR in $SourceFilesFolder"
    exit 1;
fi
echo "End program, Successfully created files"
