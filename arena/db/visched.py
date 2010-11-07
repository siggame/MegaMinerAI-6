# -*- coding: utf-8 -*-
 
import threading


class GameRecord:
  def __init__(self,priority, p1, p2, ver1, ver2,log):
    self.priority = priority
    self.p1 = p1
    self.p2 = p2
    self.ver1 = ver1
    self.ver2 = ver2
    #stores gamelog or how to get gamelog, whichever
    self.log = log

class VisScheduler:
  visq = []
  
  def __init__(self):
    self.visq = []
    self.lock = threading.Semaphore()
    
  def visualizerQueueUpdate(self, game):
    print game
    print self.lock
    with self.lock:
      found = False
      for record in self.visq:
      #finds the previous game between the same players in the same player numbers
        if game.p1 == record.p1 and game.p2 == record.p2:
          found = True
          #updates the gamelog stored
          record.log = game.log
          #Checks if its a new version
          if game.p1ver != record.p1ver or game.p2ver != record.p2ver:
            #if so, it updates the version and increases the priority (new games are more interesting than old games!)
            record.p1ver = game.p1ver
            record.p2ver = game.p2ver
            record.priority += 2*len(self.visq)
            if record.priority > 4*len(self.visq):
              record.priority = 4*len(self.visq)
      #If the game holder between those players doesn't already exist, it creates it
      if not found:
        game.priority = 2
        print game
        self.visq.append(game)
        print "visq!: ",self.visq
    return True
  
  #grabs the next thing to be visualized and makes proper adjustments
  def nextVideo(self):
    with self.lock:
      print self.visq
      if len(self.visq) > 0:
        self.visq.sort(key = lambda x: x.priority, reverse=True)
        nextUp = self.visq[0]
        nextUp.priority = 0;
        for s in self.visq[1:]:
          if nextUp.p1 not in [s.p1, s.p2]:
            s.priority += 1
          if nextUp.p2 not in [s.p1, s.p2]:
            s.priority += 1
        nextUp = nextUp.log
      else:
        nextUp = False
    return nextUp


