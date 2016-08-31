#include "ros/ros.h"
#include "serial_cpp/data_pack.h"
#include "serial_cpp/data_pack_msg.h"
#include <sstream>
#include "serial_cpp/serdes_data.h"


int main(int argc, char **argv)
{
  ros::init(argc, argv, "serial_cpp_talk");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<serial_cpp::data_pack_msg>("message", 1000);
  ros::Rate loop_rate(1);
  while (ros::ok())
  {
    serial_cpp::data_pack_msg msg;
    
    uint8_t data_buf[100];

    int cnt_data = 0;
    int i = 0;
    data_pack_t data_in;
    data_pack_t data_out;

    //init
    data_in.height = 1;
    data_in.weight = 3;
    data_in.position[0] = 5;
    data_in.position[1] = 7;

    
    cnt_data = serial_cpp::serialize_data_pack(&data_in, data_buf, 19);
    ROS_INFO("pack data cnt: %d", cnt_data);
    //printf("pack data cnt: %d\n", cnt_data);
    for(i = 0;i<11; i++){
        ROS_INFO(": %d", data_buf[i]);
    }
 
    cnt_data =  serial_cpp::deserialize_data_pack(data_buf, 19, &data_out);
    ROS_INFO("get data: %d, %d, %d,%d\n",data_out.height,data_out.weight ,data_out.position[0],data_out.position[1] );

    //printf("get data: %d, %d, %d,%d\n",data_out.height,data_out.weight ,data_out.position[0],data_out.position[1] );
    //

    msg.A = data_out.height;
    msg.B = data_out.weight;
    msg.C = data_out.position[0];

    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
