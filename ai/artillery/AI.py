# -*- coding: iso-8859-1 -*-
#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
import util

class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "Artillery Test AI"

  @staticmethod
  def password():
    return "password"

  def init(self):
    pass

  def end(self):
    pass

  def run(self):
    if(self.buildRate() > 0): # is builder
      build(self, BUILD, self.getX()+1, self.getY(), 1)
    return 1

  def __init__(self, conn):
      BaseAI.__init__(self, conn)
