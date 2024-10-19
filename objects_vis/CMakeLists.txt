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

# add_executable(draw_objects_node src/draw_objects.cpp src/utils.cpp)
# ament_target_dependencies(draw_objects_node 
#                           rclcpp 
#                           sensor_msgs 
#                           cv_bridge 
#                           image_transport 
#                           OpenCV 
#                           objects_msgs 
#                           geometry_msgs 
#                           tf2_ros 
#                           Eigen3)

# target_include_directories(draw_objects_node PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<BUILD_INTERFACE:${EIGEN3_INCLUDE_DIR}>
#   $<INSTALL_INTERFACE:include>
# )

# install(TARGETS
#   draw_objects_node
#   DESTINATION lib/${PROJECT_NAME}
# )

# add_executable(draw_objects3d_node src/draw_objects3d.cpp src/utils.cpp)
# ament_target_dependencies(draw_objects3d_node 
#                           rclcpp 
#                           sensor_msgs 
#                           cv_bridge 
#                           image_transport 
#                           OpenCV 
#                           objects_msgs 
#                           geometry_msgs 
#                           tf2_ros 
#                           Eigen3)

# target_include_directories(draw_objects3d_node PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<BUILD_INTERFACE:${EIGEN3_INCLUDE_DIR}>
#   $<INSTALL_INTERFACE:include>
# )

# install(TARGETS
# draw_objects3d_node
#   DESTINATION lib/${PROJECT_NAME}
# )
                          
# add_executable(objects2markers_node src/objects2markers.cpp src/utils.cpp)
# ament_target_dependencies(objects2markers_node 
#                           rclcpp 
#                           sensor_msgs 
#                           cv_bridge 
#                           image_transport 
#                           OpenCV 
#                           objects_msgs 
#                           geometry_msgs 
#                           tf2_ros 
#                           Eigen3 
#                           visualization_msgs 
#                           rosidl_typesupport_cpp)

# target_include_directories(objects2markers_node PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<BUILD_INTERFACE:${EIGEN3_INCLUDE_DIR}>
#   $<INSTALL_INTERFACE:include>
# )

# install(TARGETS
#   objects2markers_node
#   DESTINATION lib/${PROJECT_NAME}
#)


#----------------------------------------------------------------------------------------------
#ADD draw_objects_component
add_library(draw_objects_component SHARED 
            src/draw_objects.cpp 
            src/utils.cpp)

rclcpp_components_register_nodes(draw_objects_component "draw_objects2d_cpp::ImageViewerNode")

target_compile_definitions(draw_objects_component
  PRIVATE "DRAW_2D_OBJECTS_CPP_ROS_BUILDING_LIBRARY"
)
target_compile_options(draw_objects_component PUBLIC -Wall)
target_include_directories(draw_objects_component PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${EIGEN3_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(draw_objects_component 
                          rclcpp 
                          rclcpp_components 
                          sensor_msgs 
                          cv_bridge 
                          image_transport 
                          OpenCV 
                          objects_msgs 
                          geometry_msgs 
                          tf2_ros 
                          Eigen3)

install(TARGETS draw_objects_component
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib
)


#----------------------------------------------------------------------------------------------
#ADD draw_objects3d_component
add_library(draw_objects3d_component SHARED 
            src/draw_objects3d.cpp 
            src/utils.cpp)

rclcpp_components_register_nodes(draw_objects3d_component "draw_objects3d_cpp::DrawObjects3DNode")

target_compile_definitions(draw_objects3d_component
  PRIVATE "DRAW_3D_OBJECTS_CPP_ROS_BUILDING_LIBRARY"
)
target_compile_options(draw_objects3d_component PUBLIC -Wall)
target_include_directories(draw_objects3d_component PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${EIGEN3_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(draw_objects3d_component 
                          rclcpp 
                          rclcpp_components 
                          sensor_msgs 
                          cv_bridge 
                          image_transport 
                          OpenCV 
                          objects_msgs 
                          geometry_msgs 
                          tf2_ros 
                          Eigen3)

install(TARGETS draw_objects3d_component
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib
)


#----------------------------------------------------------------------------------------------
#ADD objects2markers_component
add_library(objects2markers_component SHARED 
            src/objects2markers.cpp 
            src/utils.cpp)

rclcpp_components_register_nodes(objects2markers_component "objects2markers::Objects2Markers")

target_compile_definitions(objects2markers_component
  PRIVATE "DRAW_MARKERS_OBJECTS_CPP_ROS_BUILDING_LIBRARY"
)
target_compile_options(objects2markers_component PUBLIC -Wall)
target_include_directories(objects2markers_component PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${EIGEN3_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(objects2markers_component 
                          rclcpp 
                          rclcpp_components 
                          sensor_msgs 
                          cv_bridge 
                          image_transport 
                          OpenCV 
                          objects_msgs 
                          geometry_msgs 
                          tf2_ros 
                          Eigen3 
                          visualization_msgs 
                          rosidl_typesupport_cpp)

install(TARGETS objects2markers_component
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib
)


#----------------------------------------------------------------------------------------------
#ADD draw_centerpoint_component
add_library(draw_centerpoint_component SHARED 
            src/draw_centerpoint.cpp)

rclcpp_components_register_nodes(draw_centerpoint_component "draw_centerpoint_cpp::CenterpointVisualization")

target_compile_definitions(draw_centerpoint_component
  PRIVATE "DRAW_CENTERPOINT_OBJECTS_CPP_ROS_BUILDING_LIBRARY"
)
target_compile_options(draw_centerpoint_component PUBLIC -Wall)
target_include_directories(draw_centerpoint_component PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${EIGEN3_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(draw_centerpoint_component 
                          rclcpp 
                          tf2 
                          rclcpp_components 
                          message_filters 
                          sensor_msgs 
                          cv_bridge 
                          image_transport 
                          OpenCV 
                          visualization_msgs 
                          objects_msgs 
                          geometry_msgs 
                          std_msgs 
                          tf2_ros 
                          Eigen3)

install(TARGETS draw_centerpoint_component
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib
)


#----------------------------------------------------------------------------------------------
# launch, param, etc...
install(DIRECTORY
  launch
  # param
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
