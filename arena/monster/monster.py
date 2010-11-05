#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
import rpyc

import scheduler

import traceback

import config
import time

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
    validNames = config.readConfig('login.cfg')
    password = validNames['admin']['password']
    
    updateServer=rpyc.connect(updateManagerName,18862)
    versions = updateServer.root.getVersions(password)
    self.serverVersion = versions['server']
    
    for i in versions:
      if i in validNames and validNames[i]['player']:
        if i not in self.scheduler.teamlist or self.scheduler.teamlist[i] != versions[i]:
          self.scheduler.updateQueue(i, versions[i])
  
  def runMatch(self, tentacle, match):
    print 'My tentacle is fight.'
    print match
    tentacle.match = match
    if hasattr(tentacle, 'job'):
      if not tentacle.job.ready:
        return False
    p1 = match.p1
    p2 = match.p2
    f = rpyc.async(tentacle.root.runGame)
    tentacle.job = f([p1, self.scheduler.teamlist[p1]], [p2, self.scheduler.teamlist[p2]], self.serverVersion)
    return True
    
    
  def run(self):
    while not self.scheduler.done():
      self.updateClients()
      print self.scheduler.teamlist
      print self.scheduler.tentq
      time.sleep(1)
      if not self.scheduler.ready():
        continue
      
      for i in self.tentacles:
        if not hasattr(i, 'job'):
          self.runMatch(i, self.scheduler.nextGame())
        elif i.job.ready:
          #Do something with the result
          #So we don't have to treat tournament schedulers differently
          print i.job.value
          self.runMatch(i, self.scheduler.nextGame())

if __name__ ==  '__main__':
    m = ArenaMonster()
    
    m.run()