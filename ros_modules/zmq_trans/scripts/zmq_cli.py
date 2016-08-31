#!/usr/bin/env python

import zmq
import time
import json 


context = zmq.Context()
socket = context.socket(zmq.PUSH)
socket.connect("tcp://127.0.0.1:1236")
msg_send = "123xxx"
msg = json.dumps({
            'header' : "fsdlkj",
            'Id' : 456,
            'value' : 123})

while True:
    socket.send(msg)
    print "Send:" 
    '''
    msg_recv = socket.recv()
    recv = json.loads(msg_recv)
    header = recv['header']
    Id = recv['Id']
    value = recv['value']
    print "get:",header,Id,value;'''
    time.sleep(1)
