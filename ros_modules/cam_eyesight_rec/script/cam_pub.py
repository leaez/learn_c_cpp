#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import rospy
import cv2
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError


def main():

    gui         = rospy.get_param("/gui")
    video_num   = rospy.get_param("/video_num")
    pub_rate    = rospy.get_param("/pub_rate")

    capture = cv2.VideoCapture(video_num)
    bridge = CvBridge()
    try:
        rospy.init_node('camera_image', anonymous=True)
        rate = rospy.Rate(pub_rate)
        image_pub = rospy.Publisher('camera/image', Image, queue_size=10)#push video image to other nodes
    except rospy.ROSInterruptException, e:
        print e

    while capture.isOpened():
        ret, frame = capture.read()
        if ret != True:
            continue

        if gui:
            cv2.imshow("Camera", frame)
            cv2.waitKey(1)
        try:
            image_pub.publish(bridge.cv2_to_imgmsg(frame, "bgr8"))
        except CvBridgeError as e:
            print(e)
        rate.sleep()
    # shutdown
    capture.release()
    if gui:
        cv2.destroyAllWindows()

if __name__ == '__main__':
    main()

