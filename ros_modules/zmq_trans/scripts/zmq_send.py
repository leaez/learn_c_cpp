#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import String
import json ,base64, socket, time, signal
from zmq_recv import zmq_recv
from zmq_trans.msg import zmq_send_msg

class zmq_send:
    def __init__(self,zmq_recv):
        rospy.init_node('zmq_send')
        self.zmq_therad = zmq_recv
        #sub  msg to send to zmq
        rospy.Subscriber('zmp_to_send', zmq_send_msg, self.zmq_rx_cb)
        signal.signal(signal.SIGINT, self.sigint_handler)
    
    def sigint_handler(self):
        self.zmq_therad.stop()
        print "main-thread exit"
        sys.exit()


    def zmq_rx_cb(self,msg):
        #print("get",msg.header)
        msg = json.dumps({
            'header' : socket.gethostname(),
            'Id' : msg.Id,#time.time(),
            'value' : msg.value})
        self.zmq_therad.send(msg)


if __name__ == '__main__':
    #zmq_address = {'send':'tcp://192.168.0.218:5556', 'recv':'tcp://192.168.0.218:5556'}
    zmq_address = {'send':'tcp://127.0.0.1:1235', 'recv':'tcp://127.0.0.1:1234'}
    zmq_thread = zmq_recv(zmq_address)
    zmq_thread.start()
    zmq_send = zmq_send(zmq_thread);


