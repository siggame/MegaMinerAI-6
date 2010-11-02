# -*- coding: iso-8859-1 -*-
from twill.commands import *

def setPassword(user, password, hint):
  go('https://password.mst.edu/cgi-bin/cgiwrap/pwchanger/changer.pl')
  fv(2, 'userid', user)
  submit()
  
  fv(3, 'oldhintans', hint)
  submit()
  
  fv(2, 'pw', password)
  fv(2, 'pw_verify', password)
  
  submit()

if __name__ == '__main__':
  input = file('passwords.txt', 'r')
  lines = [i.strip() for i in input.readlines()]
  for line in lines:
    user, hint, password = line.split('\t')
    setPassword(user, password, hint)