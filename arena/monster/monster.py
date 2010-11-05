#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
import rpyc

import scheduler

import traceback

import config

updateManagerName = 'localhost'

class ArenaMonster:
  tentacles = []
  
  def __init__(self):
    hosts = ['localhost']

    self.tentacles = []
    for i in hosts:
        try:
          self.tentacles.append(rpyc.connect(i, 18861))
          self.tentacles[-1].host = i
        except:
          traceback.print_exc()
    print "Connected to",len(self.tentacles),"tentacles"
    
    self.scheduler = scheduler.GameScheduler()
  
  def updateClients(self):
    validNames = config.readConfig("login.cfg")
    password = validNames[name]["password"]
    
    dbServer=rpyc.connect(updateManagerName,18862)
    
    
    versions
  def run(self):
    

if __name__ ==  '__main__':
    m = ArenaMonster()
    
    m.run()