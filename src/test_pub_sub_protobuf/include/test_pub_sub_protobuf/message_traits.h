#pragma once

#include "test_pub_sub_protobuf/Chatter.pb.h"
#include <ros/macros.h>
// #include <ros/traits.h>
#include <ros/message_traits.h>

#define CUSTOM_ROS_TOPIC_TRAITS(T, MD5, DATATYPE, DEFINITION)         \
namespace ros {                                                     \
namespace message_traits {                                          \
template <>                                                         \
struct MD5Sum<T> {                                                  \
    static const char *value() { return MD5; }                        \
    static const char *value(const T &) { return value(); }           \
};                                                                  \
template <>                                                         \
struct DataType<T> {                                                \
    static const char *value() { return DATATYPE; }                    \
    static const char *value(const T &) { return value(); }           \
};                                                                  \
template <>                                                         \
struct Definition<T> {                                              \
    static const char *value() { return DEFINITION; }                  \
    static const char *value(const T &) { return value(); }           \
};                                                                  \
template <>                                                         \
struct HasHeader<T> : FalseType {};                                 \
}                                                                   \
}

CUSTOM_ROS_TOPIC_TRAITS(
    test_pub_sub_protobuf::Chatter,
    "36d943046b5f520e12ac758c9f6277d7",
    "test_pub_sub_protobuf/Chatter",
    "string message\nint32 count\n"
)