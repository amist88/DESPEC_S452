#!/bin/bash
while true
do
    cd /lustre/gamma/Dryrun2021_FILES/ts_AY/
    list=$(ls -tr *.lmd)  
    for file in $list
    do
	new=$(stat --format=%s /lustre/gamma/Dryrun2021_FILES/ts_AY/$file)
	echo "$file	$new"
	echo "Adding $file to test.root"
	cd /lustre/gamma/DESPEC_S452/
	echo "go4analysis $file"
	go4analysis -file /lustre/gamma/Dryrun2021_FILES/ts_AY/$file -asf /u/despec/Dryrun2021_NEARLINE/root_output/test.root #| tee showOut.txt
	echo "Making backup."
	cp -rv /u/despec/Dryrun2021_NEARLINE/root_output/backup.root    
	echo "File $file done. Removing from folder."
	rm -fv /lustre/gamma/Dryrun2021_FILES/ts_AY/$file          
	echo "-------------------------------------------------------------------"
    done
    sleep 5 
done
