#!/bin/bash

##Setup environment
source /cvmfs/csee.gsi.de/bin/go4login
export ROOT_INCLUDE_PATH=/lustre/gamma/amistry/DESPEC_S452_NEARLINE_200421
echo "DESPEC Kronos Started at `date`"

##Set data location
#dpath=~/lustre/gamma/d004/ts/aida/

##Read in list of files to run. Format names seperated by space,tab,newline
#LISTFILE="/lustre/gamma/amistry/DESPEC_S452_NEARLINE_200421/Cluster_Submission/file_list_f187188_testfatgain.txt"

#LISTFILE="/lustre/gamma/amistry/DESPEC_S452_NEARLINE_200421/Cluster_Submission/file_list_full_f74_f75.txt"

LISTFILE="/lustre/gamma/amistry/DESPEC_S452_NEARLINE_200421/Cluster_Submission/file_list_full_188Ta.txt"

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
part=(  "${array[@]:$SLURM_ARRAY_TASK_ID:5}" ) # :5 number of files to put together -> Has to be the same in the 2 .sh scripts

echo "Running Go4!"
go4analysis -file ${part[*]} -enable-asf 1800 -asf /lustre/gamma/amistry/DESPEC_S452_NEARLINE_200421/Cluster_Submission/Nearline_Histograms/ANALY18_allTa_$SLURM_ARRAY_TASK_ID.root

#go4analysis -file ${part[*]} -enable-asf 1800 -asf /lustre/gamma/amistry/DESPEC_S452_NEARLINE_200421/Cluster_Submission/Nearline_Histograms/ANALYf74f75_$SLURM_ARRAY_TASK_ID.root

