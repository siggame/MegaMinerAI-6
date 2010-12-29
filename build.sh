#!/bin/bash

# Give build info
echo -n "Build started by " > build.log # -n flag drops ending newline
whoami | tr -d "\n" >> build.log # truncates newline char from whoami
echo -n " at " >> build.log
date >> build.log

exit 0


