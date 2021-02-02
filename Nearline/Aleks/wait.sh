#!/bin/bash

while true
do
  cd /u/ayaneva/DESPEC_Offline_S480_vMay2020/Script/
  list=$(ls -tr *.lmd)
  
  for file in $list
  do
    
    echo "Copying file $file"
    cp -rvn /u/ayaneva/DESPEC_Offline_S480_vMay2020/Script/$file /u/ayaneva/DESPEC_Offline_S480_vMay2020/Script/test/

    cd /u/ayaneva/DESPEC_Offline_S480_vMay2020/Script/test/
    if test -f "$file"; then
      echo "Waiting for new file..."
     
      continue
     
    else
      echo "Adding $file to test.root"
      cd /u/ayaneva/DESPEC_Offline_S480_vMay2020/
      
      go4analysis -file /u/ayaneva/DESPEC_Offline_S480_vMay2020/Script/test/$file -asf /u/ayaneva/DESPEC_Offline_S480_vMay2020/Script_test/test.root #| tee showOut.txt
      
      echo "-------------------------------------------------------------------"
      echo "Making backup."
      cp -rv /u/ayaneva/DESPEC_Offline_S480_vMay2020/Script_test/test.root /u/ayaneva/DESPEC_Offline_S480_vMay2020/Script_test/backup.root
      
    fi
	
      
  

  
  done
  sleep 5
  
done