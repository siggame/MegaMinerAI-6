#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
import data
import structures
from util import *
from copy import copy

def insertModel(list, model):
  if model.parent and model.parent not in list:
    insertModel(list, model.parent)
  if model not in list:
    list.append(model)

def parseData():
  models = []
  globals = data.globals
  animations = []
  for i in members(data):
    if isinstance(i, structures.Model):
      insertModel(models, i)
    elif isinstance(i, structures.Animation):
      animations.append(i)
  return {'models':models, 'globals':globals, 'animations':animations}



if __name__ == '__main__':
  objects = parseData()
  import writeC
  writeC.write(copy(objects))

  import writeServer
  writeServer.write(copy(objects))
  
  import writeJava
  writeJava.write(objects)
  """
  import writePython
  writePython.write(objects)


  import writeVisualizer
  writeVisualizer.write(objects)
  """