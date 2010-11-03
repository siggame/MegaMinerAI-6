#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-

import rpyc
from zlib import compress
from os import listdir, mkdir
from os.path import isdir, exists, join

import config.config

dbManagerName='localhost' #we should probably add a way to change this

class UpdateServer(rpyc.Service):
  def exposed_get(self, name, version):
    print "sending out",name,"version",version

    if exists( join(name,str(version)+'.tar.bz2') ):
      return open( join(name,str(version)+'.tar.bz2'),'rb').read()

    else:
      return None

def exposed_update(self, name, password, binary):
    #updates a program (a client, unless name=server)
    validNames = config.config.readConfig("login.cfg")
    if not (name in validNames and validNames[name]["password"] == password):
      return False
    
    if isdir(name):
      #already have a version, now increment by 1
      #this is a little sensative to the number of files in the directory
      #if we expect it to get polluted we should use a better method than this
      v = len(listdir(name))
    elif exists(name):
      print "Crap! Trying to make %s but it's not a directory!" % name
      return False
    else:
      mkdir(name)
      v=0
    b = open(join(name,str(v)+'.tar.bz2'),'wb')
    b.write(binary)
    b.close()
    
    #now update the database server
    try:
      db = rpyc.connect(dbManagerName,18863)
      db.root.updateVersion('name',v)
      db.close()
    except:
      import traceback
      traceback.print_exc()
      print "failed to connect to the db manager :("
    
    return True

if __name__ == "__main__":
  from rpyc.utils.server import ThreadedServer
  u = ThreadedServer(UpdateServer, port=18862)
  u.start()
