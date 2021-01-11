#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include "visualization_msgs/MarkerArray.h"
#include "geometry_msgs/Point.h"

#include "object_detection.h"

void msgCallback(const sensor_msgs::LaserScan::ConstPtr &msg)
{
	ROS_INFO("receive msg range_min = %d", msg->range_min);
	ROS_INFO("receive msg range_max = %d", msg->range_max);
}
void msgCallback2(const visualization_msgs::MarkerArray::ConstPtr &msg)
{
	ROS_INFO("receive msg markers = %d", msg->markers);
}

int main(int argc, char **argv) 
{
	ros::init(argc, argv, "object_detection_sub_node");
	ros::NodeHandle nh;

	ros::Subscriber ros_sub1 = nh.subscribe("raw_lidar", 100, msgCallback);
	ros::Subscriber ros_sub2 = nh.subscribe("marker_array", 100, msgCallback2);

	ros::spin();

	return 0;
}


