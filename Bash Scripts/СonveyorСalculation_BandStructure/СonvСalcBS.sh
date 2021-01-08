#! /bin/bash
#$1 - SourceFolder
#$2 - DstFolder
SourceFolder=$1
DstFolder=$2

#external script
scriptCalcBS=$(pwd)"/calcBandStructer.sh"
#echo $scriptCalcBS

#     block
# inner variable
#
currDir=$(pwd)
#general name for conver calculate
nameSystem=
nameCurrSystem=

#
#$1 creat Dir
function creatDir
{
    local nameDir=$1
    if ! [ -d "$nameDir" ]
    then
        mkdir "$nameDir"
    fi    
}

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
# get general name for conver calculate
nameSystem=`cat "$SourceFolder"/POSCAR | head -1 | sed 's/\\r//'`

#
# prepare output Folder
if( [ -n "$DstFolder" ] )
then
    echo "DstFolder is set: $DstFolder"
else
    echo "DstFolder is not set, creat output folder = "$name#System"_outPutFolder"
    DstFolder=$nameSystem"_outPutFolder"
fi

creatDir "$DstFolder"

cd "$DstFolder"
DstFolder=$PWD
cd "$currDir"

# check paths
echo -e "Using next dir:\n"$currDir"\n"$SourceFolder"\n"$DstFolder

#
# Main program
cd "$DstFolder"
echo $(pwd)
creatDir "$nameSystem"
cp "$SourceFolder"/POSCAR "$SourceFolder"/POTCAR "$DstFolder"/"$nameSystem"/
cd "$nameSystem"
echo -e "\n\n"$PWD
bash "$scriptCalcBS" "$SourceFolder" STD 0
cd ../

number_L=`awk 'NR==7 {print $1-1}' $"$SourceFolder"/POSCAR`
echo $number_L

for i in `seq 1 1 $number_L`
do
    cd "$DstFolder"
    nameCurrSystem="Rebuilt_""$nameSystem""_minus_"$i
    creatDir "$nameCurrSystem"
    cp "$SourceFolder"/POTCAR "$DstFolder"/"$nameCurrSystem"/
    cd "$nameCurrSystem"
    rm POSCAR
    echo $nameCurrSystem >> POSCAR
    awk '(NR > 1) && (NR < 7 ) {print $0}' "$SourceFolder"/POSCAR >> POSCAR
    let "numatoms=$number_L-$i+1"
    echo -e "    "$numatoms >> POSCAR
    let "numline=7+$numatoms+1"
    awk -v last="$numline" '(NR > 7) && (NR <= last ) {print $0}' "$SourceFolder"/POSCAR >> POSCAR
    echo $(pwd)
    cd "$nameCurrSystem"
    echo -e "\n\n"$PWD
    bash "$scriptCalcBS" "$SourceFolder" STD 0
    cd ../
done
