#include <ros/ros.h>
// #include </app/teat_pub_sub_ws/devel/include/test_pub_sub_protobuf/Chatter.pb.h>
#include "test_pub_sub_protobuf/Chatter.pb.h"   // "":适合项目内的头文件，尤其是生成的文件
#include <ros/serialization_protobuffer.h>      // <>：适合标准库或第三方库的头文件
#include <test_pub_sub_protobuf/message_traits.h>
#include <boost/shared_ptr.hpp>

void chatterCallback(const boost::shared_ptr<const test_pub_sub_protobuf::Chatter>& msg) {
    ROS_INFO("Received: %s, Count: %d", msg->message().c_str(), msg->count());
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "subscriber_node_proto");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<test_pub_sub_protobuf::Chatter>("chatter", 10, chatterCallback);
    ros::spin();
    return 0;
}