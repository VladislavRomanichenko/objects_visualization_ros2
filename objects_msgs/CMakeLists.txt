cmake_minimum_required(VERSION 3.10.2)
project(objects_msgs VERSION 0.1.1)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)


file(GLOB MSGS
  RELATIVE ${PROJECT_SOURCE_DIR}/
  ${PROJECT_SOURCE_DIR}/msg/*.msg)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${MSGS}
  DEPENDENCIES std_msgs geometry_msgs
)


ament_export_dependencies(rosidl_default_runtime)

ament_package()
