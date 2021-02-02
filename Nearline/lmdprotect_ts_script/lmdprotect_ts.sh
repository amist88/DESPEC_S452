#!/bin/bash
while true
 do
  list=$(ls -tr *lmd | head -n -1 )
  for file in $list
  do
  
  	echo "Copying files "
	chmod 444 $file
	cp -rvn $file /lustre/gamma/polettini/Scrips_071220/raw/.
	
	cd ts
	if test -f "$file"; then
    	echo "$file exists. I wait for a new file to come in"
	cd /lustre/gamma/polettini/Scrips_071220/
	continue
	else
	echo "time-stitched $file does not exists, proceed with time stitching"
	cd ~/DAQ/nearline/despec
 	./despec --output=- /lustre/gamma/polettini/Scrips_071220/$file | ./despec file://- --aida --time-stitch=wr,2000 --output=wp,/lustre/gamma/polettini/Scrips_071220/ts/$file
  	cd /lustre/gamma/polettini/Scrips_071220/
	fi
	
	
	
  done
  sleep 5
done


  
