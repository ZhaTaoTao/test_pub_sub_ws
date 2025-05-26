#include <ros/ros.h>
// #include </app/teat_pub_sub_ws/devel/include/test_pub_sub_protobuf/Chatter.pb.h>
#include "test_pub_sub_protobuf/Chatter.pb.h"
#include <ros/serialization_protobuffer.h>
#include <test_pub_sub_protobuf/message_traits.h>
#include <ros/serialization.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "publisher_node_proto");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<test_pub_sub_protobuf::Chatter>("chatter", 10);
    ros::Rate loop_rate(10); // 10 Hz

    // Test Protobuf serialization
    test_pub_sub_protobuf::Chatter test_msg;
    test_msg.set_message("Test");
    test_msg.set_count(42);
    std::string pb_str;
    test_msg.SerializeToString(&pb_str);
    ROS_INFO("Manual Protobuf serialize: size=%u", (unsigned int)pb_str.size());

    // Test ROS serialization
    ros::SerializedMessage ros_msg = ros::serialization::serializeMessage(test_msg);
    ROS_INFO("ROS serialize: size=%u", (unsigned int)ros_msg.num_bytes);

    int count = 0;
    while (ros::ok()) {
        test_pub_sub_protobuf::Chatter msg;
        msg.set_message("Hello, ROS with Protobuf! Count: " + std::to_string(count));
        msg.set_count(count++);
        ROS_INFO("Published: %s, Count: %d", msg.message().c_str(), msg.count());
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}