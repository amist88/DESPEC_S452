#!/bin/bash

# SLURM Batch Script for DESPEC Go4, NH, AKM edit for Nearline
## To run on Kronos use `sbatch go4job.sh`
## You can monitor the progress with `squeue -u <user>`

## Set the job name
#SBATCH -J despec_go4_d004f020_Nearline
## Set the folder we work in, this needs a copy of the DESPEC code
##  For performance reasons compile ELSEWHERE and copy the files to Lustre after
#SBATCH -D /lustre/gamma/amistry/DESPEC_Nearline_v1
## Save the output to log files
#SBATCH -o logs/go4_%A_%a.out.log
#SBATCH -e logs/go4_%A_%a.err.log

## Maximum run time is 8 hours, if it takes longer the run will be killed
#SBATCH --time=8:00:00
## Request 8GB of RAM per task
#SBATCH --mem-per-cpu=8G

## Set the range of LMD files for the run, and a stride of 20 per job
#SBATCH --array=0-467:10

# Load Go4
source /cvmfs/csee.gsi.de/bin/go4login
# This fixes a cling error
export ROOT_INCLUDE_PATH=/lustre/gamma/amistry/DESPEC_Nearline_v1

echo "DESPEC Kronos Started at `date`"

# These are the files to analyse!
array=(`ls /lustre/gamma/d004/ts/aida/d004f020*`)

echo "Array is $SLURM_ARRAY_TASK_ID"

part=(  "${array[@]:$SLURM_ARRAY_TASK_ID:10}" )
echo "Files to analyse: ${part[*]}"

echo "Running Go4!"
go4analysis -file ${part[*]} -enable-asf 12000 -asf d004_NearlineHistograms/d004f020_nearline_$SLURM_ARRAY_TASK_ID.root

