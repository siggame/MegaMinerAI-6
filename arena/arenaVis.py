# -*- coding: utf-8 -*-
import scheduler
import time
import rpyc
from bz2 import decompress
from subprocess import Popen

dbManagerName='r03mwwcp2.device.mst.edu'
updateServerName='r03mwwcp2.device.mst.edu'
class ArenaVisualizer:
  def __init__(self):
    self.scheduler = scheduler.VisScheduler()
    #something something Database callback something
    self.dbServer=rpyc.connect(dbManagerName,18863)
    self.dbServer.root.addCallback( lambda c1, c2, l: self.scheduler.visualizerQueueUpdate(scheduler.GameRecord(0, c1[0], c2[0], c1[1], c2[1], l)))
    
    
    
  def run(self):
    while True:
      time.sleep(1)
      next = self.scheculer.nextVideo()
      if next:
        #I am become like unto a tentacle!
        try:
          logText = self.dbServer.root.read(next.log)
          f = open('game.gamelog', 'wb')
          f.write(decompress(logText))
          f.close()
          s = Popen('./visualizer game.gamelog', shell = True)
          s.wait()
        except:
          pass

if __name__ == '__main__':
  vis = ArenaVisualizer()
  vis.run()