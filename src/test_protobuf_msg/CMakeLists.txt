cmake_minimum_required(VERSION 3.0.2)
project(test_protobuf_msg)

find_package(catkin REQUIRED COMPONENTS
roscpp
std_msgs
message_generation
)

find_package(Protobuf REQUIRED)

set(PROTO_GEN_DIR ${CATKIN_DEVEL_PREFIX}/include/${PROJECT_NAME})
file(MAKE_DIRECTORY ${PROTO_GEN_DIR})

set(PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/proto/Chatter.proto)
if(NOT EXISTS ${PROTO_FILES})
message(FATAL_ERROR "Chatter.proto not found at ${PROTO_FILES}")
endif()

# Generate Protobuf files
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

# Ensure Protobuf files are generated before building library
add_custom_target(generate_proto_files DEPENDS ${PROTO_SRCS} ${PROTO_HDRS})

add_message_files(FILES Chatter.msg)
generate_messages(DEPENDENCIES std_msgs)

add_library(proto_lib_msg ${PROTO_SRCS} ${PROTO_HDRS})
add_dependencies(proto_lib_msg generate_proto_files)
target_link_libraries(proto_lib_msg PUBLIC protobuf::libprotobuf)
target_include_directories(proto_lib_msg PUBLIC 
${PROTO_GEN_DIR}
${Protobuf_INCLUDE_DIRS}
${CMAKE_CURRENT_SOURCE_DIR}/include
${CATKIN_DEVEL_PREFIX}/include
)

# Copy generated Protobuf files to PROTO_GEN_DIR
foreach(file ${PROTO_SRCS} ${PROTO_HDRS})
get_filename_component(file_name ${file} NAME)
add_custom_command(
    OUTPUT ${PROTO_GEN_DIR}/${file_name}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${file}
            ${PROTO_GEN_DIR}/${file_name}
    DEPENDS ${file} generate_proto_files
    COMMENT "Copying ${file_name} to ${PROTO_GEN_DIR}"
)
list(APPEND PROTO_GEN_FILES ${PROTO_GEN_DIR}/${file_name})
endforeach()
add_custom_target(copy_proto_files_test ALL DEPENDS ${PROTO_GEN_FILES})

catkin_package(
CATKIN_DEPENDS roscpp std_msgs message_runtime
INCLUDE_DIRS ${PROTO_GEN_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include ${CATKIN_DEVEL_PREFIX}/include
LIBRARIES proto_lib_msg
)

include_directories(
${catkin_INCLUDE_DIRS}
${PROTO_GEN_DIR}
${Protobuf_INCLUDE_DIRS}
${CMAKE_CURRENT_SOURCE_DIR}/include
${CATKIN_DEVEL_PREFIX}/include
)

add_executable(ros_publisher src/ros_publisher.cpp)
target_link_libraries(ros_publisher ${catkin_LIBRARIES})
add_dependencies(ros_publisher ${${PROJECT_NAME}_EXPORTED_TARGETS})

add_executable(ros_subscriber src/ros_subscriber.cpp)
target_link_libraries(ros_subscriber ${catkin_LIBRARIES})
add_dependencies(ros_subscriber ${${PROJECT_NAME}_EXPORTED_TARGETS})

add_executable(proto_publisher src/proto_publisher.cpp)
target_link_libraries(proto_publisher ${catkin_LIBRARIES} proto_lib_msg ${Protobuf_LIBRARIES})
add_dependencies(proto_publisher proto_lib_msg copy_proto_files_test ${${PROJECT_NAME}_EXPORTED_TARGETS})

add_executable(proto_subscriber src/proto_subscriber.cpp)
target_link_libraries(proto_subscriber ${catkin_LIBRARIES} proto_lib_msg ${Protobuf_LIBRARIES})
add_dependencies(proto_subscriber proto_lib_msg copy_proto_files_test ${${PROJECT_NAME}_EXPORTED_TARGETS})