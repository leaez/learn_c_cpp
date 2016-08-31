#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
import zmq, json, socket
import threading
from zmq_trans.msg import zmq_recv_msg
from mDbg import *
__metaclass__ = type


TIMEOUT = 5000

"This Module is mZMQ Lib"
class zmq_recv(threading.Thread):
    def __init__(self, address):
        threading.Thread.__init__(self)
        self.context = zmq.Context()
        self.sender = self.context.socket(zmq.PUSH)
        self.receiver = self.context.socket(zmq.SUB)
        self.address = address
        self.thread_state = True
        self.zmq_rx_pub = rospy.Publisher('zmq_recv_pub', zmq_recv_msg, queue_size=10)
        self.d = rospy.Duration(1, 0)


    def send(self, msg):
        self.sender.send(msg)

    def stop(self):
        print "zmq recv thread stop!"
        self.thread_state = False
        signal.alarm(1) #break select method

    def run(self):
        self.connect()
        DBG_Printf(True, 'connect success')
        while self.thread_state:
            socks = dict(self.poller.poll())
            if socks.get(self.receiver) == zmq.POLLIN:
                msg_cli = self.receiver.recv()
                try:
                    recv = json.loads(msg_cli)

                    recv_msg = zmq_recv_msg()
                    recv_msg.header = recv['header']
                    recv_msg.Id = recv['Id']
                    recv_msg.value = recv['value']
                    self.zmq_rx_pub.publish(recv_msg)

                except ValueError,e:
                    ERR_Printf(True, e)
            else:
                WAR_Printf(True, "No results received")
            rospy.sleep(self.d);

    def connect(self):
        try:
            self.sender.connect(self.address['send'])
            self.receiver.connect(self.address['recv'])
            self.receiver.setsockopt(zmq.SUBSCRIBE, '')
            self.poller = zmq.Poller()
            self.poller.register(self.receiver, zmq.POLLIN)
        except Exception, e:
            ERR_Printf(True, e)

if __name__ == '__main__':
    DBG_Printf(True, "zmq_recv")
    zmq_address = {'send':'tcp://192.168.0.218:5556', 'recv':'tcp://192.168.0.218:5559'}
    mzmq = zmq_recv(zmq_address)
    mzmq.start()

