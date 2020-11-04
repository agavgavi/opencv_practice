#!/bin/bash

argumentsArray=("lbp_front" "lbp_front_improved" "haar_front_alt" "haar_front_alt2" "haar_front_tree" "haar_front_default")
echo "Starting Test Program looping through cases"
rm -r ../output/*
mkdir ../output/{lbp_front,lbp_front_improved,haar_front_alt,haar_front_alt2,haar_front_tree,haar_front_default}
cd build-*
for val1 in ${argumentsArray[*]}; do
	echo ""
	echo "Using" $val1
	start=`date +%s`
	
	./opencv_security_cam_test $val1
	end=`date +%s`
	runtime=$((end-start))
	echo "RUNTIME: " $runtime
	echo ""
done
echo ""
