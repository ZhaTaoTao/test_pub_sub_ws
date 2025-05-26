#ifndef ROSCPP_SERIALIZATION_PROTOBUFFER_H
#define ROSCPP_SERIALIZATION_PROTOBUFFER_H

#include <google/protobuf/message.h>
#include <test_protobuf_msg/Chatter.pb.h>
#include <ros/serialization.h>

namespace ros {
namespace serialization {

template <typename T>
struct Serializer<T, typename std::enable_if<std::is_base_of<
                         ::google::protobuf::Message, T>::value>::type> {
  template <typename Stream>
  inline static void write(Stream& stream, const T& t) {
    uint32_t len = t.ByteSizeLong();
    stream.next(len);
    uint8_t* buffer = stream.advance(len);
    t.SerializeToArray(buffer, len);
  }

  template <typename Stream>
  inline static void read(Stream& stream, T& t) {
    uint32_t len;
    stream.next(len);
    if (len > 0) {
      const char* data_ptr = reinterpret_cast<const char*>(stream.advance(len));
      t.ParseFromArray(data_ptr, len);
    } else {
      t.Clear();
    }
  }

  inline static uint32_t serializedLength(const T& t) {
    return 4 + static_cast<uint32_t>(t.ByteSizeLong());
  }
};

} // namespace serialization
} // namespace ros

#endif // ROSCPP_SERIALIZATION_PROTOBUFFER_H