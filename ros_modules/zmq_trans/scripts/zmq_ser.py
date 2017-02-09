#!/usr/bin/env python

import zmq
import time
import json

context = zmq.Context()
sender = context.socket(zmq.PUB)
sender.bind("tcp://127.0.0.1:1234")

receiver = context.socket(zmq.PULL)
receiver.bind("tcp://127.0.0.1:1235")

while True :
    message = receiver.recv()
    recv = json.loads(message)
    header = recv['header']
    Id = recv['Id']
    value = recv['value']
    print "get:",header,Id,value;

    msg = json.dumps({
            'header' : "hhhhh",
            'Id' : 234,#time.time(),
            'value': 678})

    sender.send(msg)
    time.sleep(1)
