#!/bin/bash
### A.K.M Basic script to hadd histograms and send them to the nearline folder for webbrowser
    echo -e "hadd script for summing batch processed histograms " 
    echo -e "Try not to give the output the same name as the inputs "
    echo -e "At the end of the hadd, the completed .root file will automatically copy to /WWW/despec/go4-jsroot/NearlineFiles. This will require the despec password"
    echo -e "You will then be given the option to move the old batch made .root files if no longer needed" 
    
	echo -e "Enter input file (can use wildcards e.g. S452*): " 
	read input
	echo -e "Enter output file (doesn't need .root extension): "
	read output
	
	echo "Input file name :  $input , Output file name:  $output"
    
 		hadd -j 100 $output $input
        mv "$output" "${output}.root"

 		scp -r ${output}.root despec@lxpool:/WWW/despec/go4-jsroot/NearlineFiles
		
    echo -e "Do you wish to move the batch made split .root files temporarily to the backup folder? (keeps here clean) [Y/N]" 
    read response
    if [[ "$response" =~ ^([Y])$ ]]
then
    echo "Move batch made histograms (output will still be stored here, inputs moved to backup)"
    mv $input backup/
else
    echo "Old batch made histograms are kept here, if you need them then please move them to another folder"
fi
