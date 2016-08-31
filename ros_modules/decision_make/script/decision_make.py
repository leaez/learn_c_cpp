#!/usr/bin/env python
# license removed for brevity

import rospy
from std_msgs.msg import String
from zmq_trans.msg import zmq_recv_msg
from zmq_trans.msg import zmq_send_msg

def callback(data):
    rospy.loginfo("get: %s", data.value)


def main():
    pub = rospy.Publisher('send_to_m4', String, queue_size=10)
    rospy.init_node('decision_make', anonymous=True)
    rate = rospy.Rate(10) # 10hz

    #
    rospy.Subscriber("m4_serial_data", String, dm_callback)
    rospy.Subscriber("zmq_recv_msg", String, callback)
    rospy.Subscriber("m4_serial_data", String, callback)

    
    while not rospy.is_shutdown():
        to_m4_msg = to_m4_msg()
        to_m4_msg.a = 123;
        pub.publish(to_m4_msg)
        rate.sleep()

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass

