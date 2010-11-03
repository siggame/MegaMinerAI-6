#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
import sys

input = file(sys.argv[1], 'r')
output = file(sys.argv[2], 'w')

for line in input:
  name, hint, password = [i.strip() for i in line.split('\t')]
  
  output.write('[%s]\npassword = %s\nscreenName = Unassigned\n\n' % (name, password))