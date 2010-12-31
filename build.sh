#!/bin/bash

# Give build info
echo -n "Build started by " | tee build.log # -n flag drops ending newline
whoami | tr -d "\n" >> build.log # truncates newline char from whoami
echo -n " at " >> build.log
date >> build.log
echo "" >> build.log # Throw a newline on the end...

# Start building!


echo "--- Starting Parser Build --" >> build.log
echo "cd'ing to ./" 

exit 0

