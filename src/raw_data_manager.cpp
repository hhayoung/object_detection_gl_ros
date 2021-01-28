#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include "object_detection.h"

#include "object_detection_gl_ros/Distance.h"

#include <vector>

#define PI 3.14159265359

void msgCallback(const sensor_msgs::LaserScan::ConstPtr &msg) {

	float *arr = new float[1000];
	std::vector<int> v;
	int flag = 0;

	ros::NodeHandle nh_pub;
	ros::Publisher dist_pub = nh_pub.advertise<object_detection_gl_ros::Distance>("distances", 1);

	object_detection_gl_ros::Distance dist_msg;

	// 1000개 데이터중 일정 각도의 거리값 저장
	for(int i=444;i<557;i++){
		arr[i] = msg->ranges[i];

		//ROS_INFO("front distance = %.2f cm", arr[i]*100);
		if(arr[i] < 0.6) {
			v.push_back(i);
			flag = 1;
		}
	}
	// 왼쪽 거리값 데이터
	float left_dist = msg->ranges[999];
	// 마찬가지로 cm단위로 데이터 넣음
	dist_msg.left_dist = left_dist * 100;
	//ROS_INFO("left = %d cm", dist_msg.left_dist);

	if(flag==1) {
		int median = v.size() / 2;
		float front_dist = arr[v[median]];
		// cm단위로 데이터 넣음
		dist_msg.front_dist = front_dist * 100;
		ROS_INFO("front = %d cm", dist_msg.front_dist);

		// width 값 구하기(오차있음)
		float r = front_dist;
		// ROS_INFO("v.front r = %.2f", arr[v.front()]);
		// ROS_INFO("v.back r = %.2f", arr[v.back()]);
		// ROS_INFO("avg r = %.2f", r);

		float degree = ((v.back()+1) * 0.18) - ((v.front()+1) * 0.18);
		ROS_INFO("degree = %f", degree);
		float seta = degree * PI / 180; // degree -> radian
		ROS_INFO("seta = %f", seta); // 최대 20도가 끝

		float width = 2 * r * sin(seta / 2);
		ROS_INFO("width = %.2f",width);

	}
	// 다 쓰고 반환
	delete arr;

	while(ros::ok()){
		dist_pub.publish(dist_msg); // 데이터 보내기
		ros::spinOnce(); // 있어야 while문 벗어남
	}
	
}


int main(int argc, char **argv) 
{
	ros::init(argc, argv, "raw_data_manager");
	ros::NodeHandle nh;

	ros::Subscriber raw_lidar_sub = nh.subscribe("raw_lidar", 100, msgCallback);

	ros::spin();

	return 0;
}




