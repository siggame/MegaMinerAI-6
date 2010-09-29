import rpyc

if __name__ ==  '__main__':
    import traceback
    hosts = [i.strip() for i in open('serverList.txt', 'r').readlines()]
    
    conns = []
    for i in hosts:
        try:
          conns.append(rpyc.connect(i, 18861))
          conns[-1].host = i
        except:
          traceback.print_exc()
        
    
    for conn in conns:
        print conn.host, conn.root.getFree()
