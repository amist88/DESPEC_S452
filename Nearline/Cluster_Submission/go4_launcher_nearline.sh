#!/bin/bash

##Setup environment
source /cvmfs/csee.gsi.de/bin/go4login
export ROOT_INCLUDE_PATH=/lustre/gamma/virgotesting/DESPEC_S452_Nearline
echo "DESPEC Kronos Started at `date`"

##Set data location
#dpath=~/lustre/gamma/d004/ts/aida/

##Read in list of files to run. Format names seperated by space,tab,newline
LISTFILE="/lustre/gamma/virgotesting/DESPEC_S452_Nearline/Nearline_Scripts/files_list.txt"

##Count number of files
NFILES=$(cat ${LISTFILE} | wc -l)
echo "Analysing" $NFILES "Files"

##Read names from list file
declare -a array
while IFS= read -r line
do
    array+=($line)
done < "$LISTFILE"

echo "Array is $SLURM_ARRAY_TASK_ID"
part=(  "${array[@]:$SLURM_ARRAY_TASK_ID:10}" )

echo "Running Go4!"
go4analysis -file ${part[*]} -enable-asf 12000 -asf /lustre/gamma/virgotesting/DESPEC_S452_Nearline/Nearline_Histograms/d004NearlineTest_$SLURM_ARRAY_TASK_ID.root

