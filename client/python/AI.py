# -*- coding: iso-8859-1 -*-
#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
import util

import random

direction = 'lrud'

class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "Shell AI"

  @staticmethod
  def password():
    return "password"

  def init(self):
    pass

  def end(self):
    pass

  def run(self):
    for i in self.bots:
      if i.getOwner() == self.playerID():
        i.move(random.choice(direction))
        if i.getBuildRate():
          i.build(random.choice(self.types), i.getX()+1, i,getY(), 1)
    return 1

  def __init__(self, conn):
    BaseAI.__init__(self, conn)
