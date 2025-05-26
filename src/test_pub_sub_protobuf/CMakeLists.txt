cmake_minimum_required(VERSION 3.0.2)
project(test_pub_sub_protobuf)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

find_package(Protobuf REQUIRED)

# Create devel/include directory early
set(PROTO_GEN_DIR ${CATKIN_DEVEL_PREFIX}/include/${PROJECT_NAME})
file(MAKE_DIRECTORY ${PROTO_GEN_DIR})

# Debug: Print paths
message(STATUS "CATKIN_DEVEL_PREFIX: ${CATKIN_DEVEL_PREFIX}")
message(STATUS "PROTO_GEN_DIR: ${PROTO_GEN_DIR}")
message(STATUS "Protobuf_INCLUDE_DIRS: ${Protobuf_INCLUDE_DIRS}")

# Find proto files
set(PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/proto/Chatter.proto)
message(STATUS "Proto files: ${PROTO_FILES}")
if(NOT EXISTS ${PROTO_FILES})
  message(FATAL_ERROR "Chatter.proto not found in ${CMAKE_CURRENT_SOURCE_DIR}/proto")
endif()

# Generate Protobuf files
protobuf_generate_cpp(
  PROTO_SRCS PROTO_HDRS
  ${PROTO_FILES}
)

# Add message files
add_message_files(
  FILES
  Chatter.msg
)

# Generate messages
generate_messages(
  DEPENDENCIES
  std_msgs
)

# Create library for Protobuf files
add_library(proto_lib ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(proto_lib PUBLIC protobuf::libprotobuf)
target_include_directories(proto_lib PUBLIC 
  ${PROTO_GEN_DIR} 
  ${Protobuf_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  /opt/ros/noetic/include
)

# Move generated files to PROTO_GEN_DIR
foreach(file ${PROTO_SRCS} ${PROTO_HDRS})
  get_filename_component(file_name ${file} NAME)
  add_custom_command(
    OUTPUT ${PROTO_GEN_DIR}/${file_name}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${file}
            ${PROTO_GEN_DIR}/${file_name}
    DEPENDS ${file}
    COMMENT "Copying ${file_name} to ${PROTO_GEN_DIR}"
  )
  list(APPEND PROTO_GEN_FILES ${PROTO_GEN_DIR}/${file_name})
endforeach()
add_custom_target(copy_proto_files ALL DEPENDS ${PROTO_GEN_FILES})

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs message_runtime
  INCLUDE_DIRS ${PROTO_GEN_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include /opt/ros/noetic/include
  LIBRARIES proto_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PROTO_GEN_DIR}
  ${Protobuf_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  /opt/ros/noetic/include
)

add_executable(publisher_node_proto src/publisher_node_proto.cpp)
target_link_libraries(publisher_node_proto ${catkin_LIBRARIES} proto_lib ${Protobuf_LIBRARIES})
add_dependencies(publisher_node_proto proto_lib copy_proto_files ${${PROJECT_NAME}_EXPORTED_TARGETS})

add_executable(subscriber_node_proto src/subscriber_node_proto.cpp)
target_link_libraries(subscriber_node_proto ${catkin_LIBRARIES} proto_lib ${Protobuf_LIBRARIES})
add_dependencies(subscriber_node_proto proto_lib copy_proto_files ${${PROJECT_NAME}_EXPORTED_TARGETS})
