#include <ros/ros.h>
#include <test_protobuf_msg/Chatter.h>
#include <ros/serialization.h>

void callback(const test_protobuf_msg::Chatter::ConstPtr &msg) {
    static int count = 0;
    static double total_time = 0;

    // Deserialize
    ros::Time t0 = ros::Time::now();
    ros::SerializedMessage ser_msg = ros::serialization::serializeMessage(*msg);
    test_protobuf_msg::Chatter tmp;
    ros::serialization::deserializeMessage(ser_msg, tmp);
    total_time += (ros::Time::now() - t0).toSec();

    if (++count == 100000) {
        printf("ROS Deserialization Time: %.6f s\n", total_time);
        count = 0;
        total_time = 0;
        }
    }

int main(int argc, char **argv) {
    ros::init(argc, argv, "ros_subscriber");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("chatter_ros", 1000, callback);
    ros::spin();
    return 0;
}