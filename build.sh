#!/bin/bash

# Give build info
echo -n "Build started by " | tee build.log # -n flag drops ending newline
whoami | tr -d "\n" | tee -a build.log # truncates newline char from whoami
echo -n " at " | tee -a build.log
date | tee -a build.log
echo "" | tee -a build.log # Throw a newline on the end...

# Start building!



echo "Starting parser build..." | tee -a build.log
echo "Moving to parser directory..." | tee -a build.log
cd ./visualizer/parser/
echo "Building parser..." | tee -a build.log
make |& tee -a ../../build.log # pipes sterr AND stout to tee

exit 0

