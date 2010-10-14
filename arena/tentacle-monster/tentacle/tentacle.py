from rpyc import Service

class GladiatorService(Service):
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
