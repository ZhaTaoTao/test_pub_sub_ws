#include <ros/ros.h>
#include <test_protobuf_msg/Chatter.pb.h>
#include <test_protobuf_msg/serialization_protobuffer.h>
#include <test_protobuf_msg/message_traits.h>
#include <ros/serialization.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "proto_publisher");
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<test_protobuf_msg::Chatter>("chatter_proto", 1000);

  const int NUM_MSGS = 2000000;
  const int BATCH_SIZE = 100000; // 增大批量大小
  test_protobuf_msg::Chatter msg;
  msg.set_message("Hello, Performance Test!", 22);
  msg.set_count(42);

  // 预热发布，稳定通信
  for (int i = 0; i < 1000; ++i) {
    pub.publish(msg);
  }
  ros::Duration(0.5).sleep();

  // 测量序列化时间和大小
  ros::Time start = ros::Time::now();
  uint64_t total_size = 0;
  for (int i = 0; i < NUM_MSGS; ++i) {
    uint8_t buffer[128];
    uint32_t len = msg.ByteSizeLong();
    msg.SerializeToArray(buffer, len);
    total_size += len;
  }
  double serialize_time = (ros::Time::now() - start).toSec();

  // 测量发布吞吐量
  start = ros::Time::now();
  for (int i = 0; i < NUM_MSGS; i += BATCH_SIZE) {
    for (int j = 0; j < BATCH_SIZE && (i + j) < NUM_MSGS; ++j) {
      pub.publish(msg);
    }
  }
  double publish_time = (ros::Time::now() - start).toSec();

  printf("Protobuf Serialization Time: %.6f s\n", serialize_time);
  printf("Protobuf Message Size: %.2f bytes (avg)\n", total_size / (double)NUM_MSGS);
  printf("Protobuf Throughput: %.2f messages/s\n", NUM_MSGS / publish_time);

  return 0;
}