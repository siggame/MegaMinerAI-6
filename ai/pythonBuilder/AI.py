# -*- coding: iso-8859-1 -*-
#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
import random

class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "Shell AI"

  @staticmethod
  def password():
    return "password"

  #This function is called once, before your first turn
  def init(self):
    pass

  #This function is called each time it is your turn
  #Return true to end your turn, return false to ask the server for updated information
  def run(self):
    if self.playerID() == 0:
      mine = [i for i in self.bots if i.getOwner() == 0 and i.getPartOf() == 0]
      while max([i.getSize() for i in mine]) < 16:
        mine = [i for i in self.bots if i.getOwner() == 0 and i.getPartOf() == 0]
        for i in mine:
          print i
          i.build(self.types[1], i.getX() + i.getSize(), i.getY(), i.getSize())
        yield 1
        yield 1
        yield 1
        yield 1
        mine = [i for i in self.bots if i.getOwner() == 0 and i.getPartOf() == 0]
        for i in mine:
          print i
          i.build(self.types[1], i.getX(), i.getY() + i.getSize(), i.getSize())
        yield 1
        yield 1
        yield 1
        yield 1
        mine = [i for i in self.bots if i.getOwner() == 0 and i.getPartOf() == 0]
        for i in mine:
          print i
        size = max([i.getSize() for i in mine])
        mine[0].combine(mine[1], mine[2], mine[3])
        yield 1
        mine = [i for i in self.bots if i.getOwner() == 0 and i.getPartOf() == 0]
      while True:
        yield 1
    
    else:
      mine = [i for i in self.bots if i.getOwner() == 1 and i.getPartOf() == 0]
      while max([i.getSize() for i in mine]) < 16:
        mine = [i for i in self.bots if i.getOwner() == 1 and i.getPartOf() == 0]
        for i in mine:
          print i
          i.build(self.types[1], i.getX() - i.getSize(), i.getY(), i.getSize())
        yield 1
        yield 1
        yield 1
        yield 1
        mine = [i for i in self.bots if i.getOwner() == 1 and i.getPartOf() == 0]
        for i in mine:
          print i
          i.build(self.types[1], i.getX(), i.getY() - i.getSize(), i.getSize())
        yield 1
        yield 1
        yield 1
        yield 1
        mine = [i for i in self.bots if i.getOwner() == 1 and i.getPartOf() == 0]
        for i in mine:
          print i
        size = max([i.getSize() for i in mine])
        mine[0].combine(mine[1], mine[2], mine[3])
        yield 1
        mine = [i for i in self.bots if i.getOwner() == 1 and i.getPartOf() == 0]
      while True:
        yield 1

  def __init__(self, conn):
    BaseAI.__init__(self, conn)