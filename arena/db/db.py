#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
import MySQLdb
import rpyc
import datetime
import os
from random import randint

import config

logdir = '/web/static/'

versions = {}
logNum = len(os.listdir(logdir+'logs'))

db=MySQLdb.connect(host = 'localhost',
                   user = 'root',
                   passwd="",
                   db="fwog_web")

class DBManager(rpyc.Service):
  callbackFuns = []
  def exposed_addCallback(f):
    callbackFuns.append(f)
  def exposed_read(self, log):
    return open(logdir+'%s.gamelog.bz2' % log).read()
  def exposed_catalog(self, password, log, c1, c2, sv, startTime, winner_int):
    global logNum
    validNames = config.readConfig("login.cfg")
    if validNames['admin']['password'] != password:
      return None
    
    print "logging a game into the database....:"
    print "client1=",c1[0]
    print "client1 version=",c1[1]
    print "client2=",c2[0]
    print "client2 version=",c2[1]
    print "server version=",sv
    print "start time=",startTime
    print "winner=",winner_int

    filename = 'logs/%s.gamelog.bz2' % logNum
    logNum += 1
    
    c=db.cursor()
    c.execute("SELECT max(id) FROM fwog_web_game")
    max_id = c.fetchone()[0]

    if max_id == None:
      max_id = 0

    c.execute("SELECT a.id FROM auth_user a, mstusername m WHERE a.username = m.username AND m.mstname = '%s' " % (c1[0].lower(),))
    try:
      c1id = c.fetchone()[0]
    except:
      print "OH NO! Is",c1[0],"registered on the web server??"
      c1id = 0

    c.execute("SELECT a.id FROM auth_user a, mstusername m WHERE a.username = m.username AND m.mstname = '%s' " % (c2[0].lower(),))
    try:
      c2id = c.fetchone()[0]
    except:
      print "OH NO! Is",c2[0],"registered on the web server??"
      c2id = 0

    query = "INSERT INTO fwog_web_game " + \
        "VALUES (%d, %d, %d, %d, %d, %d, %d, '%s','%s')" % \
        (max_id+1, #game log id
         c1id, #client 1
         c2id, #client 2
         c1[1], #client 1 version
         c2[1], #client 2 version
         winner_int%2, #client 1 score
         winner_int/2, #client 2 score
         filename, #log filename
         str(datetime.datetime.now()) ) #current time
    c.execute(query)
    db.commit()
            
    f=open(logdir+filename,'wb')
    f.write(log)
    f.close()
    print "log saved at: ", logdir+filename
    
    for fun in self.callbackFuns:
      try:
        fun(c1,c2,logNum-1)
      except:
        self.callbackFuns.remove(fun)

if __name__=='__main__':
  from rpyc.utils.server import ThreadedServer
  d = ThreadedServer(DBManager,port=18863)
  d.start()
