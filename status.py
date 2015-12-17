# -*- coding: utf-8 -*-
"""
Created on Tue Nov 24 18:32:12 2015

@author: dmitryduev
"""

import time
import datetime
#import math

from ws4py.client.threadedclient import WebSocketClient

import json
from collections import OrderedDict

#%%
class telemetry(object):
    '''
        Get telemetry data
        
    '''
    def __init__(self, conf_file = 'config.json'):
        # parse config json file
        with open(conf_file) as f:
            self.conf = json.load(f, object_pairs_hook=OrderedDict)
            
        self.data = OrderedDict()
    
    def skeleton(self):
        '''
            Return 'skeletons' for building the html template
        '''
        skelet = OrderedDict()
        # iterate over systems
        for system in self.conf.keys():
            # reserve a spot:
            skelet[system] = {'globals':OrderedDict(), 'subs':OrderedDict()}

            # iterate over global params and subsystems
            for key in self.conf[system].keys():
                # skip this:
                if key == 'data-file':
                    continue
                # global params:
                val = self.conf[system][key]
                if type(val) == type([]):
                    skelet[system]['globals'][key] = []
                
                # 'sub-systems'
                elif type(val) == type(OrderedDict()):
                    skelet[system]['subs'][key] = OrderedDict()
                    for key2 in val.keys():
                        skelet[system]['subs'][key][key2] = []

        return skelet
    
    def fetch(self):
        '''
            Extract telemetry data
        '''
        # iterate over systems
        for system in self.conf.keys():
            # status data file (one-liner):
            status_file = self.conf[system]['data-file']
            try:
                with open(status_file) as sf:
                    line = sf.read().split()
            except:
                # no money - no honey
                continue
            if len(line)<5:
                continue
            # reserve a spot for global params and subsys data:
            self.data[system] = {'globals':OrderedDict(), 'subs':OrderedDict()}
            # iterate over global params and subsystems
            for key in self.conf[system].keys():
                # skip this:
                if key == 'data-file':
                    continue
                # global params:
                val = self.conf[system][key]
                if type(val) == type([]):
                    # get value from the proper position in the telemetry file
                    self.data[system]['globals'][key] = line[val[0][0]] if len(val[0])==1 \
                        else ' '.join(line[val[0][0]:val[0][-1]])
                    tmp = self.data[system]['globals'][key]
                    # get color:
                    color_code = 'default'

                    ## it's not str8forward with the Time stamp - 
                    ## deal with it separately
                    ## config.json lists ranges in seconds WRT datetime.now()
                    # beware that it should all be in UTC!
                    if 'time' in key.lower() or 'date' in key.lower():
                        then = datetime.datetime.strptime(\
                                self.data[system]['globals'][key], \
                                '%Y-%m-%d %H:%M:%S.%f')
                        now = datetime.datetime.utcnow()
                        tmp = (then-now).total_seconds()

                    # for the rest of the global params it is str8forward
                    for code, rng in self.conf[system][key][1].iteritems():
                        if type(rng[0])==type(u"") and tmp in rng:
                            color_code = code
                        elif type(rng[0])==type([]):
                            for rn in rng:
                                if rn[0]<= float(tmp) < rn[1]:
                                    color_code = code

                    # get plotting switch:
                    plot_switch = self.conf[system][key][2]
                    # get 'critical' switch:
                    critical_switch = self.conf[system][key][3]
                    self.data[system]['globals'][key] = \
                                [self.data[system]['globals'][key], \
                                    color_code, plot_switch, critical_switch]
                
                # 'sub-systems'
                elif type(val) == type(OrderedDict()):
                    self.data[system]['subs'][key] = OrderedDict()
                    for key2 in val.keys():
                        val2 = self.conf[system][key][key2][0]
                        self.data[system]['subs'][key][key2] = line[val2[0]] \
                            if len(val2)==1 else ' '.join(line[val2[0]:val2[-1]])
                        tmp = self.data[system]['subs'][key][key2]
                        # get color:
                        color_code = 'default'
                        for code, rng in self.conf[system][key][key2][1].iteritems():
        #                    print tmp, rng, tmp in rng, type(rng[0])==type([])
                            if type(rng[0])==type(u"") and tmp in rng:
                                color_code = code
                            elif type(rng[0])==type([]):
                                for rn in rng:
        #                            print rn, float(tmp)
                                    if rn[0]<= float(tmp) < rn[1]:
        #                                print 'bingo!', tmp, code
                                        color_code = code
                                        break
                        # get plotting switch:
                        plot_switch = self.conf[system][key][key2][2]
                        # get 'critical' switch:
                        critical_switch = self.conf[system][key][key2][3]
                        self.data[system]['subs'][key][key2] = \
                                [self.data[system]['subs'][key][key2], \
                                    color_code, plot_switch, critical_switch]
        return self.data

#%%
class RoboAOstatus(object):
    def __init__(self, host, conf_file = 'config.json'):
        self.running = False

        self.client = RoboAOstatusWebSocketClient(host)
        self.client.connect()
        
        # init telemetry class object:
        self.telemetry = telemetry(conf_file)
        
    def run(self):
        try:
            self.running = True
            while self.running:
                if self.client.terminated:
                    break
                
                # fetch telemetry
                data = self.telemetry.fetch()

                # stream it to clients
                self.client.send(json.dumps(data))

#                time.sleep(0.15)
                time.sleep(1)
        finally:
            self.terminate()
            
    def terminate(self):        
        self.running = False
        
        if self.client is not None and not self.client.terminated:
            self.client.close()
            self.client._th.join()
            self.client = None
        
class RoboAOstatusWebSocketClient(WebSocketClient):
        def received_message(self, m):
            pass

#%%
if __name__ == '__main__':
    import argparse
    
    parser = argparse.ArgumentParser(description='Send telemetry to CherryPy Server')
    parser.add_argument('--host', default='127.0.0.1')
    parser.add_argument('-p', '--port', default=8080, type=int)
    parser.add_argument('--ssl', action='store_true')
    args = parser.parse_args()

    aps = RoboAOstatus(host='ws://'+args.host+':'+str(args.port)+'/ws')
    try:
        aps.run()
    except KeyboardInterrupt:
        aps.terminate()
