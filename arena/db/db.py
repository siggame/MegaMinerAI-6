#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
#import mysqldb
import rpyc
from random import randint

import config

versions = {}
logNum = 0

class DBManager(rpyc.Service):
  def exposed_updateVersion(self, password, name, version):
    validNames = config.readConfig("login.cfg")
    if validNames['admin']['password'] != password:
      return None
    #update the version of program 'name' in the version database
    versions[name] = version
  
  def exposed_getVersions(self, password):
    validNames = config.readConfig("login.cfg")
    if validNames['admin']['password'] != password:
      return None
    #update the version of program 'name' in the version database
    
    return versions
  
  def exposed_catalog(self, password, log, c1, c2, sv, startTime):
    global logNum
    validNames = config.readConfig("login.cfg")
    if validNames['admin']['password'] != password:
      return None
    
    print "logging a game into the database....:"
    print "client1=",c1[0]
    print "client1 version=",c1[1]
    print "client2=",c2[0]
    print "client2 version=",c2[1]
    print "server version=",sv
    print "start time=",startTime

    filename = 'logs/%s.gamelog' % logNum
    logNum += 1
    
    f=open(filename,'wb')
    f.write(log)
    print "log saved at: ", filename

if __name__=='__main__':
  from rpyc.utils.server import ThreadedServer
  d = ThreadedServer(DBManager,port=18863)
  d.start()
