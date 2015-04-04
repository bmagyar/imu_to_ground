#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Quaternion.h>

class Node
{
private:
  ros::NodeHandle _nh;
  ros::Subscriber _sub;
  ros::Publisher _pub;
  sensor_msgs::Imu imu_msg;

public:
  Node()
  {
    _sub = _nh.subscribe("quat", 10, &Node::callback, this);
    _pub = _nh.advertise<sensor_msgs::Imu>("imu", 10);
    imu_msg.header.frame_id = "base_link";
  }

  void callback(const geometry_msgs::Quaternion& quat_msg)
  {
    imu_msg.header.seq++;
    imu_msg.header.stamp = ros::Time::now();
    imu_msg.orientation = quat_msg;
    imu_msg.linear_acceleration.x = 1.0;
    imu_msg.linear_acceleration.y = 0.2;
    imu_msg.linear_acceleration.z = 0.2;

    _pub.publish(imu_msg);
  }
};

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "quat_to_imu_node");
  Node node;
  ros::spin();
}
