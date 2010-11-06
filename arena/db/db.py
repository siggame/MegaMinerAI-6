#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
#import mysqldb
import rpyc
from random import randint

import config

versions = {}
logNum = 0

db=MySQLdb.connect(host = 'localhost',
                   user = 'root',
                   passwd="",
                   db="fwog_web")

class DBManager(rpyc.Service):
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

    filename = 'logs/%s.gamelog' % logNum
    logNum += 1
    
    c=db.cursor()
    c.execute("SELECT max(id) FROM fwog_web_game")
    max_id = c.fetchone()[0]

    if max_id == None:
      max_id = 0

    c.execute("SELECT id FROM auth_user WHERE username = '%s'" % (c1[0].lower(),))
    c1id = c.fetchone()[0]
    c.execute("SELECT id FROM auth_user WHERE username = '%s'" % (c2[0].lower(),))
    c2id = c.fetchone()[0]

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
            
    f=open('/web/static/',filename,'wb')
    f.write(log)
    print "log saved at: ", filename

if __name__=='__main__':
  from rpyc.utils.server import ThreadedServer
  d = ThreadedServer(DBManager,port=18863)
  d.start()
