#!/bin/bash

logfilename=build.log # name of log
rootdir=$PWD # where this script is located
logfilepath=$rootdir/$logfilename
buildNumber=(python build_number.py)

# Give build info
echo -n "Build " | tee $logfilepath # -n flag drops ending newline
echo -n $buildNumber | tee -a $logfilepath 
echo -n " started by " | tee -a $logfilepath 
whoami | tr -d "\n" | tee -a $logfilepath # truncates newline char from whoami
echo -n " at " | tee -a $logfilepath
date | tee -a $logfilepath
echo "" | tee -a $logfilepath # Throw a newline on the end...

# Start building!

# Build the parser
echo "Starting parser build..." | tee -a $logfilepath
cd ./visualizer/parser
make |& tee -a $logfilepath # |& pipes sterr AND stout to tee
cd $rootdir

# Build visualizer
echo "Starting visualizer build..." | tee -a $logfilepath
cd ./visualizer
make |& tee -a $logfilepath # |& pipes sterr AND stout to tee
cd $rootdir

exit 0

