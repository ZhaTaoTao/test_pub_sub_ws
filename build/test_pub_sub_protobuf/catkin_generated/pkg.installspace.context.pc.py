# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include;/opt/ros/noetic/include".split(';') if "${prefix}/include;/opt/ros/noetic/include" != "" else []
PROJECT_CATKIN_DEPENDS = "roscpp;std_msgs;message_runtime".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lproto_lib".split(';') if "-lproto_lib" != "" else []
PROJECT_NAME = "test_pub_sub_protobuf"
PROJECT_SPACE_DIR = "/app/teat_pub_sub_ws/install"
PROJECT_VERSION = "0.0.1"
