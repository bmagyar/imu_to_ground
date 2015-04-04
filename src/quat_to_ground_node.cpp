#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_broadcaster.h>

class Node
{
private:
  ros::NodeHandle _nh;
  ros::Subscriber _sub;
  ros::Publisher _pub;

  geometry_msgs::PoseStamped pose_msg;
  tf::TransformBroadcaster tf_broadcaster;
  tf::StampedTransform transform;

public:
  Node()
  {
    _sub = _nh.subscribe("quat", 10, &Node::callback, this);
    _pub = _nh.advertise<geometry_msgs::PoseStamped>("pose", 10);
    pose_msg.header.frame_id = "base_link";

    transform.child_frame_id_ = "base_link";
    transform.frame_id_ = "base_footprint";
  }

  void callback(const geometry_msgs::Quaternion& quat_msg)
  {
    pose_msg.header.seq++;
    pose_msg.header.stamp = ros::Time::now();
    pose_msg.pose.orientation = quat_msg;

    _pub.publish(pose_msg);

    tf::Quaternion tf_quat;
    tf::quaternionMsgToTF(quat_msg, tf_quat);
    transform.setRotation(tf_quat);
    transform.stamp_ = ros::Time::now();

    tf_broadcaster.sendTransform(transform);
  }
};

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "quat_to_ground_node");
  Node node;
  ros::spin();
}
