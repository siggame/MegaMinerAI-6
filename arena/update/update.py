import rpyc
from zlib import compress
from os import listdir,mkdir
from os.path import isdir,exists
dbManagerName='localhost'
class UpdateServer(rpyc.Service):
  def exposed_get(self, name, version):
    print "sending out",name,"version",version
    if exists(name+'/'+str(version)+'.gz'):
      return open(name+'/'+str(version)+'.gz','rb').read()
    elif exists(name+'/'+str(version)):
      return compress(open(name+'/'+str(version),'rb').read())
    else:
      return None
  def exposed_update(self, name, binary):
    #updates a program (a client, unless name=server)
    if isdir(name):
      #already have a version, now increment by 1
      v = int(listdir(name)[-1])+1
    else:
      mkdir(name)
      v=0
    b = open(name+'/'+str(v),'wb')
    b.write(binary)
    b.close()
    c = compress(binary)
    cf = open(name+'/'+str(v)+".gz",'wb')
    cf.write(c)
    cf.close()
    #now update the database server
    try:
      db = rpyc.connect(dbManagerName,18863)
      db.root.updateVersion('name',v)
      db.close()
    except:
      import traceback
      traceback.print_exc()
      print "failed to connect to the db manager :("
if __name__ == "__main__":
  from rpyc.utils.server import ThreadedServer
  u = ThreadedServer(UpdateServer, port=18862)
  u.start()
