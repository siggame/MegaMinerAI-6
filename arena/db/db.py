#import mysqldb
import rpyc
from zlib import decompress
from random import randint
class DBManager(rpyc.Service):
  def exposed_updateVersion(self,name,version):
    #update the version of program 'name' in the version database
    pass
  def exposed_catalog(self,clog,c1,c1v,c2,c2v,sv,startTime,serverName):
    print "logging a game into the database....:"
    print "client1=",c1
    print "client1 version=",c1v
    print "client2=",c2
    print "client2 version=",c2v
    print "server version=",sv
    print "start time=",startTime
    print "servername=",serverName
    n=randint(0,1000)
    d=decompress(clog)
    log=open('logs/'+str(n),'wb')
    log.write(d)
    print "log saved at: logs/",n

if __name__=='__main__':
  from rpyc.utils.server import ThreadedServer
  d = ThreadedServer(DBManager,port=18863)
  d.start()
