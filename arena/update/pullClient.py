#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-

import rpyc
import sys

if __name__ == '__main__':
  host = sys.argv[1]
  password = sys.argv[2]
  name = sys.argv[3]
  version = sys.argv[4]
  
  server = rpyc.connect(host,18862)
  text = server.root.get(password, name, version)
  if text:
    f = file(str(version) + '.tar.bz2', 'wb')
    f.write(text)
  else:
    print "Pull failed. :("
  
  server.close()