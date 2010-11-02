import rpyc
import multiprocessing
import os 
import traceback
import zlib
import stat
import time
dbManagerName='localhost'
updateServerName='localhost'
class GladiatorService(rpyc.Service):
  def update(self, name, version):
    try:
      updateServer=rpyc.connect(updateServerName,18862)
      zfile = updateServer.root.get(name, version)
      dfile = zlib.decompress(zfile)
      if not os.path.isdir(name):
        os.mkdir(name)
      path = name+'/'+str(version)
      f = open(path,'wb')
      f.write(dfile)
      f.close()
      os.chmod(path,stat.S_IRWXU)
      print "updated",name
    except:
      traceback.print_exc()
      print "Failed to connet to the update server :("

  def startServer(self, sv):
    os.chdir('server')
    os.execvp('python',['python',str(sv)])
  
  def startClient(self, name, version, args):
    os.chdir(name)
    os.execv(str(version), args)

  def exposed_runGame(self,c1,c1v,c2,c2v,sv):
    #check versioning:
    if not os.path.exists(c1+'/'+str(c1v)):
      self.update(c1,c1v)
    if not os.path.exists(c2+'/'+str(c2v)):
      self.update(c2,c2v)
    if not os.path.exists('server/'+str(sv)):
      self.update('server',sv)
    
    startTime=time.time()
    server = multiprocessing.Process(target=self.startServer,args=[sv])
    server.start()
    time.sleep(0.5)
    player1 = multiprocessing.Process(target=self.startClient,args=[c1,c1v,[str(c1v),'localhost']])
    player1.start()
    time.sleep(0.5)
    player2 = multiprocessing.Process(target=self.startClient,args=[c2,c2v,[str(c2v),'localhost',str(1)]])
    player2.start()
    #wait for gamelog
    while player1.is_alive() or player2.is_alive():
      time.sleep(5)
    #stop server since it's currently looking for more connections
    server.terminate()
    logfile=open('server/logs/1.gamelog','rb')
    log=logfile.read()
    logfile.close()
    clog=zlib.compress(log)
    try:
      dbServer=rpyc.connect(dbManagerName,18863)
      dbServer.root.catalog(clog,c1,c1v,c2,c2v,sv,startTime,os.uname()[1])
    except:
      traceback.print_exc()

  def exposed_getFree(self):
    f = open('/proc/meminfo', 'r')
    lines = f.readlines()
    total = int(lines[0].split(' ')[-2])
    active = int(lines[5].split(' ')[-2])
    
    return total - active

if __name__ == "__main__":
    from rpyc.utils.server import ThreadedServer
    
    t = ThreadedServer(GladiatorService, port = 18861)
    
    t.start()
