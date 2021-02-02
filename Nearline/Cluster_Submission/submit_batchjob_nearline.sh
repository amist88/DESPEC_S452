#!/bin/bash
##Read in list of files to run
LISTFILE="files_list.txt"
declare -a size
while IFS= read -r line
do
    size+=($line)
done < "$LISTFILE"

##Submit job
sbatch -J despec_go4_d004f020_Nearline -D /lustre/gamma/virgotesting/DESPEC_S452_Nearline -o logs/go4_%A_%a.out.log -e logs/go4_%A_%a.err.log \
	--time=8:00:00 --mem-per-cpu=8G --array=0-${#size[@]}:10 -- ./Nearline_Scripts/go4_launcher_nearline.sh
