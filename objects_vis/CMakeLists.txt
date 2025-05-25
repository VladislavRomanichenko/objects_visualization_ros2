cmake_minimum_required(VERSION 3.5)
project(objects_vis VERSION 1.0.0)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(objects_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2 REQUIRED)
find_package(rosidl_typesupport_cpp REQUIRED)
find_package(message_filters REQUIRED)


include_directories(${EIGEN3_INCLUDE_DIR})

#Component lib
add_library(objects_vis_lib SHARED
  src/draw_objects_node.cpp
  src/draw_objects3d_node.cpp
  src/objects2markers_node.cpp
  src/dynamic_objects2markers_node.cpp
  src/utils.cpp
)

rclcpp_components_register_nodes(objects_vis_lib "objects_vis::DrawObjects")
rclcpp_components_register_nodes(objects_vis_lib "objects_vis::DrawObjects3D")
rclcpp_components_register_nodes(objects_vis_lib "objects_vis::Objects2Markers")
rclcpp_components_register_nodes(objects_vis_lib "objects_vis::DynamicObjects2Markers")

ament_target_dependencies(objects_vis_lib
  rclcpp
  rclcpp_components
  std_msgs
  sensor_msgs
  objects_msgs
  geometry_msgs
  tf2_geometry_msgs
  visualization_msgs
  cv_bridge
  image_transport
  OpenCV
  Eigen3
  tf2_ros
  tf2
  rosidl_typesupport_cpp
  message_filters
)

target_compile_options(objects_vis_lib PUBLIC -Wall)
target_include_directories(objects_vis_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${EIGEN3_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
)

add_executable(publish_random_objects test/publish_random_objects.cpp)
target_link_libraries(publish_random_objects objects_vis_lib)

add_executable(draw_objects src/draw_objects_exec.cpp)
add_executable(draw_objects3d src/draw_objects3d_exec.cpp)
add_executable(objects2markers src/objects2markers_exec.cpp)
add_executable(dynamic_objects2markers src/dynamic_objects2markers_exec.cpp)

target_link_libraries(draw_objects objects_vis_lib)
target_link_libraries(draw_objects3d objects_vis_lib)
target_link_libraries(objects2markers objects_vis_lib)
target_link_libraries(dynamic_objects2markers objects_vis_lib)

install(TARGETS objects_vis_lib
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib
)

install(TARGETS
  draw_objects
  draw_objects3d
  objects2markers
  dynamic_objects2markers
  publish_random_objects
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(
  rclcpp
  rclcpp_components
  std_msgs
  sensor_msgs
  objects_msgs
  geometry_msgs
  tf2_geometry_msgs
  visualization_msgs
  cv_bridge
  image_transport
  OpenCV
  Eigen3
  tf2_ros
  tf2
  rosidl_typesupport_cpp
  message_filters
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
