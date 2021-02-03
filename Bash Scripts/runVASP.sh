#! /bin/bash
# $1 - choose vasp (STD, GAM, NCL ...)
# $2 - choose runParametr
# $3 - flagTest

typeBuildVASP=$1
runParametr=$2
flagTest=$3

# Output File
logFile=LOGFILE


# Block Internal variables
# required for the script to work correctly

# Full path to script file
ABSOLUTE_SCRIPTNAME=`readlink -e $0`

# Path to directory containing this script
SCRIPT_DIRECTORY=`dirname "$ABSOLUTE_SCRIPTNAME"`

# Full path to config runVasp
PathToConfigRunVASP=$SCRIPT_DIRECTORY/config_runVASP

# Name Setion in config_runVASP
DBV="Different builds of VASP"
DROV="Different run options of VASP"
configRunVASPListSection="DBV DROV"

# End Block Internal varibles



#  Function working with the configuration file config_runVASP,
# which retrieves the values of the options specified in this file.
#  There are several sections in the file, each section begins
# with a # sign followed by the section name.
#  Next is a list of options of the form key = value
function getOptions {
    # $1 nameSections
    # $2 choice : 1 - get only keys of options
    #             2 - get keys and values of options
    #             3 - get value of options
    # $3 nameOption
    local nameSections=$1
    local choice=$2
    local nameOption=$3

    if ( [ $choice != 1  ] && [ $choice != 3 ] )
    then
        choice=0
        nameOption=
    else
        if( [ $choice != 3 ] )
        then
            nameOption=
        fi
    fi

    awk -v nS="$nameSections" -v ch=$choice -v nO=$nameOption '/^[#]/{flagPrintOption = 0} (/^[#]/)&&($0~nS){flagPrintOption = 1} (!/^$/)&&flagPrintOption{if(flagPrintOption >1 ) { if(!nO) print $(ch); else {if($1 == nO) for(i=3;i<=NF;i++){printf "%s ", $(i);}}} else flagPrintOption++;}' "$PathToConfigRunVASP"
}


# variables of function setValueOptionToValueOption
# input variables
ErrorStringNoSetOption="Error: You need set parametrs:"
ErrorStringNotKey=
listSection=
Section=
ValueOption=

function setValueOptionToValueOption {
    listOptions=$(getOptions "$Section" 1)
    if [ -z "$ValueOption" ]
    then
        # if NameOption not set (i.e. empty),
        # throw an error not specified option 
        echo $ErrorStringNoSetOption
        for curSection in $listSection
        do
            #
            eval valueCurSection=\$$curSection

            if [ -n "$valueCurSection" ]
            then
                echo -e "[OPTION $valueCurSection]"
                getOptions "$valueCurSection" 2
                echo
            fi
        done
        exit 1
    else
        currect=0
        for option in $listOptions
        do
            if [ $ValueOption == $option ]
            then
                currect=1
                break
            fi
        done
        if [[ currect -ne 0  ]]
        then
            ValueOption=$(getOptions  "$DBV" 3 "$ValueOption")
        else
            echo $ErrorStringNotKey
            getOptions "$Section" 2
            exit 1
        fi
    fi
}


# Set type Build VASP
# set input variables of function setValueOptionToValueOption
listSection=$configRunVASPListSection
Section="$DBV"
ValueOption=$typeBuildVASP
ErrorStringNotKey="Error: $ValueOption - This type build VASP is not. Pleas take currect option:"

# run function
setValueOptionToValueOption

# function output
DBV=
typeBuildVASP=$ValueOption
#


# Set runParametr
# set input variables of function setValueOptionToValueOption
listSection=$configRunVASPListSection
Section="$DROV"
ValueOption=$runParametr
ErrorStringNotKey="Error: $ValueOption - This OPTION RUN is not. Pleas take currect option:"

# run function
setValueOptionToValueOption

# function output
DROV=
runParametr=$ValueOption
#


# main function runVASP
if [ -n "$flagTest" ]
then
    echo -e "Test: $runParametr $typeBuildVASP"
else
    if [ -f "$logFile" ]
    then
        rm "$logFile"
    fi
    #
    $runParametr $typeBuildVASP >> "$logFile"
    exitFlag=$?
    if [[ $exitFlag -eq 0 ]]
    then
        echo "VASP : $runParametr $typeBuildVASP : Successfully created files in $(pwd)"
        echo "VASP : $runParametr $typeBuildVASP : successfully finish $exitFlag" >> "$logFile"
    else
        echo "VASP : $runParametr $typeBuildVASP : ERROR, pleas look at file _LOGFILE in $(pwd)"
        echo "VASP : $runParametr $typeBuildVASP : fail job $exitFlag" >> "$logFile"
        exit 1
    fi
fi
