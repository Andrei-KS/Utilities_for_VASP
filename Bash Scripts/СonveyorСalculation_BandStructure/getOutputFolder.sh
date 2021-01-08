#! /bin/bash

#get output Folder for files to will getted from calcBandStructure.sh

outputDir=outputFiles

echo outputDir

FileForCopy="CONTCAR DOSCAR EIGENVAL INCAR KPOINTS OSZICAR OUTCAR POSCAR POTCAR vasprun.xml _LOGFILE"

FolderForCopy=`ls -l | awk '/^d[r-][w-][x-]/{print $NF}' | awk '/DOS|Ek/{print $0}'`" ./"

#if directory exist it not create this directory
function creatDirectory {
    local nameDir=$1
    if ! [ -d $nameDir ]
    then
        mkdir $nameDir
    fi
}


creatDirectory $outputDir
cd $outputDir

for directory in $FolderForCopy
do
    echo $directory
    creatDirectory $directory
    for currentFile in $FileForCopy
    do
        #echo $currentFile
        cp ../$directory/$currentFile $directory/
    done
done

cd ..


