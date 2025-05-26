#ifndef TEST_PROTOBUF_MSG_MESSAGE_TRAITS_H
#define TEST_PROTOBUF_MSG_MESSAGE_TRAITS_H

#include <ros/message_traits.h>
#include <test_protobuf_msg/Chatter.pb.h>

namespace ros {
namespace message_traits {

template <>
struct MD5Sum<test_protobuf_msg::Chatter> {
  static const char* value() { return "d41d8cd98f00b204e9800998ecf8427e"; }
  static const char* value(const test_protobuf_msg::Chatter&) { return value(); }
};

template <>
struct DataType<test_protobuf_msg::Chatter> {
  static const char* value() { return "test_protobuf_msg/Chatter"; }
  static const char* value(const test_protobuf_msg::Chatter&) { return value(); }
};

template <>
struct Definition<test_protobuf_msg::Chatter> {
  static const char* value() { return "bytes message\nint32 count\n"; }
  static const char* value(const test_protobuf_msg::Chatter&) { return value(); }
};

} // namespace message_traits
} // namespace ros

#endif // TEST_PROTOBUF_MSG_MESSAGE_TRAITS_H