# -*- coding: utf-8 -*-
"""
Created on Thu Dec 10 00:50:29 2015

@author: dmitryduev
"""

import subprocess
import time

if __name__ == '__main__':
    
#    server = subprocess.Popen('./server-daemon.sh', shell=True)
#    print server.pid
    
    # wait for the server to start, then begin to send telemetry
#    time.sleep(2)
#    status = subprocess.Popen('./status-daemon.sh', shell=True)
    
    # finally, run the png generating engine
#    png = subprocess.Popen('./png-daemon.sh', shell=True)
    png = subprocess.Popen('watch -n 0.5 ./lib/png2', shell=True)
    
#    sig1, sig2 = 1, 1
#    while sig1 != 0 and sig2 != 0:
#        time.sleep(2)
#        server = subprocess.Popen('python server.py', shell=True)
#        time.sleep(2)
#        status = subprocess.Popen('python status.py', shell=True)
#        sig1 = server.wait()
#        sig2 = status.wait()
#        print 'lala'*100, sig1
    
#    server = subprocess.Popen('python server.py', shell=True)
#    
#    sig = server.wait()
#    if sig != 0:
#        time.sleep(2)
#        
#    print 'lala'*100, sig
#    server.communicate()