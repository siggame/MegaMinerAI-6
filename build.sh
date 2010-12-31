#!/bin/bash

logfilename=build.log # name of log
rootdir=$PWD # where this script is located
logfilepath=$rootdir/$logfilename

# Give build info
echo -n "Build started by " | tee $logfilepath # -n flag drops ending newline
whoami | tr -d "\n" | tee -a $logfilepath # truncates newline char from whoami
echo -n " at " | tee -a $logfilepath
date | tee -a $logfilepath
echo "" | tee -a $logfilepath # Throw a newline on the end...

# Start building!

# Build the parser
echo "Starting parser build..." | tee -a $logfilepath
cd ./visualizer/parser
make |& tee -a $logfilepath # |& pipes sterr AND stout to tee

exit 0

