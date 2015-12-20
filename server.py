# -*- coding: utf-8 -*-
"""
Created on Fri Nov 13 18:55:46 2015

@author: dmitryduev
"""

from status import telemetry

import argparse

import cherrypy
#from cherrypy.lib import auth_digest

#from jinja2 import Environment, FileSystemLoader
#env = Environment(loader=FileSystemLoader('templates'))
from jinja2 import Template

import os

import numpy as np

from ws4py.server.cherrypyserver import WebSocketPlugin, WebSocketTool
from ws4py.websocket import WebSocket
from ws4py.messaging import TextMessage

class WebSocketHandler(WebSocket):
    def received_message(self, m):
        cherrypy.engine.publish('websocket-broadcast', m)

    def closed(self, code, reason="A client left the room without a proper explanation."):
        cherrypy.engine.publish('websocket-broadcast', TextMessage(reason))

#%%
class Root(object):
    
    def __init__(self, path, host, port, ssl=False):
        self.path = path
        self.host = host
        self.port = port
        self.scheme = 'wss' if ssl else 'ws'
        
    @cherrypy.expose
    def index(self):
        # get skeleton from the config file:
        skelet = telemetry().skeleton()
        
        # render:
#        tmpl = env.get_template('status.html')

        with open('templates/status.html', 'r') as f:
            html_tmpl = f.read()
        tmpl = Template(html_tmpl)
        return tmpl.render(host=self.host, port=self.port, \
                           skelet=skelet, layout='one')        
        
    @cherrypy.expose
    def image(self):

        # render:
#        tmpl = env.get_template('image.html')
        with open('templates/image.html', 'r') as f:
            html_tmpl = f.read()

#        return tmpl.render(args=np.arange(10))
        return html_tmpl
        
    @cherrypy.expose
    def ws(self):
#        cherrypy.log("Handler created: %s" % repr(cherrypy.request.ws_handler))
        cherrypy.request.ws_handler
        
        
#%%
if __name__ == '__main__':
    
#    import logging
#    from ws4py import configure_logger
#    configure_logger(level=logging.DEBUG)

    parser = argparse.ArgumentParser(description='Echo CherryPy Server')
    parser.add_argument('--host', default='0.0.0.0')
    parser.add_argument('-p', '--port', default=8080, type=int)
    parser.add_argument('--extip', default='127.0.0.1')
    parser.add_argument('-ep', '--extport', default=8080, type=int)
    parser.add_argument('--ssl', action='store_true')
    args = parser.parse_args()


    # set some protection    
#    USERS = {'admin': 'robo@0'}
    
    # configure cherrypy
    cherrypy.config.update({'server.socket_host': args.host, #'0.0.0.0',
                             'server.socket_port': args.port, #8080,
                             'server.thread_pool' : 8#,
                             #'log.access_file': 'server_access.log',
                             #'log.error_file': 'server_actions.log'
                            })
    
    conf = {
         '/': {
             'tools.sessions.on': True,
             'tools.staticdir.root': os.path.abspath(os.getcwd()),
#             'tools.auth_digest.on': True,
#             'tools.auth_digest.realm': 'hola!',
#             'tools.auth_digest.get_ha1': auth_digest.get_ha1_dict_plain(USERS),
#             'tools.auth_digest.key': 'd8765asdf6c787ag333'
         },
         '/ws': {
            'tools.websocket.on': True,
            'tools.websocket.handler_cls': WebSocketHandler
            },
         '/static': {
             'tools.staticdir.on': True,
#             'tools.staticdir.dir': os.path.join(os.path.abspath(os.getcwd()), 'public')
             'tools.staticdir.dir': './public',
#             'tools.auth_digest.on': True,
#             'tools.auth_digest.realm': 'hola!',
#             'tools.auth_digest.get_ha1': auth_digest.get_ha1_dict_plain(USERS),
#             'tools.auth_digest.key': 'd8765asdf6c787ag333'
         }
    }
    
    # start sockets
    WebSocketPlugin(cherrypy.engine).subscribe()
    cherrypy.tools.websocket = WebSocketTool()
    
    path = './'
    cherrypy.quickstart(Root(path=path, host=args.extip, port=args.extport, \
                        ssl=args.ssl), '/', conf)
