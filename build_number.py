#!/usr/bin/env python

import pickle
import os

def buildNum():
  #if file exists
  try:
    inPklFile = open('buildNumber.pickle', 'rb')
    i = pickle.load(inPklFile)
    inPklFile.close()
    i += 1
    outPklFile = open('buildNumber.pickle', 'wb')
    pickle.dump(i, outPklFile)
    outPklFile.close()
    return i
  #else make one
  except: 
    i = 1 # start at 1
    outPklFile = open('buildNumber.pickle', 'wb')
    pickle.dump(i, outPklFile)
    outPklFile.close()
  return i
  
if __name__ == "__main__":
  buildNum()

