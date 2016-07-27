#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy,roslib
from std_msgs.msg import String
import cv2
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import numpy as np

def SubccriberHandler(data):
    bridge = CvBridge()
    try:
        cv_image = bridge.imgmsg_to_cv2(data, 'bgr8')
        yuv_image = cv2.cvtColor(cv_image, cv2.COLOR_BGR2YUV)
        cv2.imshow("Image", yuv_image)
        cv2.waitKey(3)

    except CvBridgeError as e:
        print e

if __name__ == '__main__':
    print "camera display"
    cv2.namedWindow("Image")
    cv2.waitKey(2000)

    rospy.init_node('camera_display', anonymous=True)
    rospy.Subscriber("camera/image", Image, SubccriberHandler)
    rospy.spin()

    #cv2.destroyAllWindows()
