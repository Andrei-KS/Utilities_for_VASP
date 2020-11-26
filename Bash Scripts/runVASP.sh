#! /bin/bash
#$1 choose vasp (STD, GAM, NCL ...)
#$2 choose runParametr
#$3 - flagTest

typeVASP=$1
runParametr=$2
flagTest=$3

logFile=LOGFILE

function getOptions {
    #$1 nameSections
    #$2 choice : 1 - get only options
    #            2 - get options and discreption
    #            3 - get options value
    #$3 nameOption
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

    awk -v nS=$nameSections -v ch=$choice -v nO=$nameOption '/^[#]/{flagPrintOption = 0} (/^[#]/)&&($0~nS){flagPrintOption = 1} (!/^$/)&&flagPrintOption{if(flagPrintOption >1 ) { if(!nO) print $(ch); else {if($1 == nO) for(i=3;i<=NF;i++){printf "%s ", $(i);}}} else flagPrintOption++;}' config_runVASP
}

listOptions=$(getOptions OPTION 1)


if [ -z "$typeVASP" ]
then
  echo "You need set parametrs: runVASP.sh [OPTION VASP]"
  getOptions OPTION 0
  echo -e "\n[OPTION RUN]"
  getOptions RUN 0
  exit 1
else
    currect=0
    for option in $listOptions
    do
        if [ $typeVASP == $option ]
        then
            currect=1
            break
        fi
    done
    if [[ currect -ne 0  ]]
    then
        typeVASP=$(getOptions OPTION 3 $typeVASP)
    else
        echo "Error: $typeVASP - This OPTION VASP is not. Pleas take currect option:"
        getOptions OPTION 0
        exit 1
    fi
fi

listOptions=$(getOptions RUN 1)

if [ -z "$runParametr" ]
then
    echo "You need set parametrs: runVASP.sh [OPTION RUN]"
    getOptions RUN 0
    exit 1
else
    currect=0
    for option in $listOptions
    do
        if [ $runParametr == $option ]
        then
            currect=1
            break
        fi
    done
    if [[ currect -ne 0  ]]
    then
        runParametr=$(getOptions RUN 3 $runParametr)
    else
        echo "Error: $runParametr - This OPTION RUN is not. Pleas take currect option:"
        getOptions RUN 0
        exit 1
    fi
fi

if [ -n "$flagTest" ]
then
    echo -e "Test: $runParametr $typeVASP"
else
    if [ -f "$logFile" ]
    then
        rm "$logFile"
    fi
    $runParametr $typeVASP >> "$logFile"
    exitFlag=$?
    if [[ $exitFlag -eq 0 ]]
    then
        echo "VASP : $runParametr $typeVASP : Successfully created files in $(pwd)"
        echo "VASP : $runParametr $typeVASP : successfully finish $exitFlag" >> "$logFile"
    else
        echo "VASP : $runParametr $typeVASP : ERROR, pleas look at file _LOGFILE in $(pwd)"
        echo "VASP : $runParametr $typeVASP : fail job $exitFlag" >> "$logFile"
        exit 1
    fi
fi
