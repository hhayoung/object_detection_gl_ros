#include <ros/ros.h>

#include "object_detection_gl_ros/Distance.h"

void msgCallback(const object_detection_gl_ros::Distance::ConstPtr &msg) {
	int front_dist = msg->front_dist;
	int left_dist = msg->left_dist;

	ROS_INFO("front_dist = %d cm", front_dist);
	ROS_INFO("left_dist = %d cm", left_dist);
}

int main(int argc, char **argv) 
{
	ros::init(argc, argv, "test_file");
	ros::NodeHandle nh;

	ros::Subscriber distance_sub = nh.subscribe("distances", 1, msgCallback);

	ros::spin();

	return 0;
}
