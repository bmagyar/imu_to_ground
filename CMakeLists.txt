cmake_minimum_required(VERSION 2.8.3)
project(imu_to_ground)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  sensor_msgs
  tf
)

catkin_package(
  CATKIN_DEPENDS geometry_msgs roscpp sensor_msgs tf
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(quat_to_imu src/quat_to_imu_node.cpp)
target_link_libraries(quat_to_imu ${catkin_LIBRARIES})

add_executable(quat_to_ground src/quat_to_ground_node.cpp)
target_link_libraries(quat_to_ground ${catkin_LIBRARIES})

#############
## Install ##
#############

install(TARGETS quat_to_ground quat_to_imu
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
