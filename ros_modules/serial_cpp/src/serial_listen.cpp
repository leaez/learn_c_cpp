#include "ros/ros.h"
#include "serial_cpp/data_pack.h"
#include "serial_cpp/data_pack_msg.h"
#include "serial_cpp/serdes_data.h"


void messageCallback(const serial_cpp::data_pack_msg::ConstPtr& msg)
{
  ROS_INFO("I heard: [%d] [%d] [%d]", msg->A, msg->B, msg->C);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "serial_cpp_listen");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("message", 1000, messageCallback);
  ROS_INFO("yes");

  ros::spin();
  return 0;
}
