#pragma once

#include <rclcpp/rclcpp.hpp>

#include <string>
#include <memory>
#include <chrono>
#include <iostream>
#include <functional>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>

#include <objects_msgs/msg/dynamic_object.hpp>
#include <objects_msgs/msg/dynamic_object_array.hpp>

#include <std_msgs/msg/header.hpp>
#include <std_msgs/msg/float32_multi_array.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/time_synchronizer.h>

#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>

#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

namespace draw_centerpoint_cpp{

    class CenterpointVisualization : public rclcpp::Node
    {
    public:
        CenterpointVisualization(const rclcpp::NodeOptions& options);

    private:
        void initializeParameter();

        void CenterpointCallback(const objects_msgs::msg::DynamicObjectArray::ConstSharedPtr& objects);

        //void pub_markers(objects_msgs::msg::DynamicObjectArray out_msg, double robot_pose[6], bool visualization_on);

        rclcpp::Subscription<objects_msgs::msg::DynamicObjectArray>::SharedPtr obj_sub_;
        rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;

        std::string ns;
        std::string fixed_frame;
        std::string objects;
        bool visualization_on;

        float COLOR_1[4] = {0.2, 0.7, 0.2, 0.8};
        float COLOR_2[4] = {0.2, 0.5, 0.8, 0.8};
        float COLOR_3[4] = {0.6, 0.1, 0.0, 0.5};
        
    };
}//namespace draw_centerpoint_cpp