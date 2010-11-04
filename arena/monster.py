#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
import rpyc

if __name__ ==  '__main__':
    import traceback
    hosts = ['localhost']

    tentacles = []
    for i in hosts:
        try:
          tentacles.append(rpyc.connect(i, 18861))
          tentacles[-1].host = i
        except:
          traceback.print_exc()
    print "Connected to",len(tentacles),"tentacles"
    
    for tentacle in tentacles:
        print tentacle.host, tentacle.root.runGame(['client', 0], ['client', 0], 0)
