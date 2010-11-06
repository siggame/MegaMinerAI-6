#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
import rpyc
from subprocess import Popen, PIPE, STDOUT
import os, shutil
from os.path import isdir, exists, join
import traceback
from bz2 import compress, decompress
from tarfile import TarFile
from StringIO import StringIO
import time

import config

dbManagerName='r03mwwcp2.device.mst.edu'
updateServerName='r03mwwcp2.device.mst.edu'
class GladiatorService(rpyc.Service):
  def update(self, name, version, target):
    shutil.rmtree(target)
    os.mkdir(target)
    try:
      updateServer=rpyc.connect(updateServerName,18862)
      validNames = config.readConfig("login.cfg")
      password = validNames['admin']['password']
      tar = updateServer.root.get(password, name, version)
      
      s = StringIO(decompress(tar))
      f = TarFile(mode='r', fileobj=s)
      
      f.extractall(target)
      print "updated",name
      return True
    except:
      traceback.print_exc()
      print "Failed to connet to the update server :("
      return False


  def startServer(self):
    s = Popen('./main.py -arena', stdin = None, stdout = None, stderr = None, shell = True, cwd = 'server')
    return s
  
  def startClient1(self):
    c = Popen('./run localhost', stdout = None, stderr = STDOUT, shell = True, cwd = 'client1')
    return c
  
  def startClient2(self):
    c = Popen('./run localhost 0', stdout = None, stderr = STDOUT, shell = True, cwd = 'client2')
    return c

  def exposed_runGame(self, c1, c2, sv):
    #check versioning:
    self.update(c1[0], c1[1], 'client1')
    self.update(c2[0], c2[1], 'client2')
    self.update('server',sv, 'server')
    
    startTime = time.time()
    
    server = self.startServer()
    time.sleep(1)
    
    player1 = self.startClient1()
    time.sleep(1)
    print 'Waiting for game created'
    if not exists(join('server', 'created')):
      player1.kill()
      server.kill()
      return -1
    
    
    player2 = self.startClient2()
    time.sleep(1)
    
    print 'Waiting for game started'
    if not exists(join('server', 'started')):
      print 'aww'
      player1.kill()
      player2.kill()
      server.kill()
      return -2
    
    print 'playing game'
    #wait for gamelog
    while time.time() < startTime + 600:
      server.poll()
      if server.returncode is not None:
        break
      time.sleep(5)
    
    print 'the game is finished!'
    
    if server.returncode is None:
      player1.kill()
      player2.kill()
      server.kill()
      return 0
    
    print 'I wonder who won!'
    
    time.sleep(2)
    player1.kill()
    player2.kill()
    
    
    logfile=open('server/logs/1.gamelog.bz2','rb')
    log=logfile.read()
    try:
      validNames = config.readConfig("login.cfg")
      password = validNames['admin']['password']
      
      dbServer=rpyc.connect(dbManagerName,18863)
      dbServer.root.catalog(password, log, c1, c2, sv,startTime)
    except:
      traceback.print_exc()
    
    if not exists(join('server', 'winner')):
      return 0
    if 'Player 0 wins' in file(join('server', 'winner'), 'r').read():
      return 1
    return 2

  def exposed_getFree(self):
    f = open('/proc/meminfo', 'r')
    lines = f.readlines()
    total = int(lines[0].split(' ')[-2])
    active = int(lines[5].split(' ')[-2])
    
    return total - active

if __name__ == "__main__":
    from rpyc.utils.server import ThreadedServer
    
    t = ThreadedServer(GladiatorService, port = 18861)
    
    t.start()
