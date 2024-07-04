#pragma once

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <std_msgs/msg/color_rgba.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <objects_msgs/msg/object_array.hpp>

#include "../include/utils.hpp"

namespace objects2markers{

    using namespace std::chrono_literals;

    class Objects2Markers : public rclcpp::Node {
    public:
        Objects2Markers(const rclcpp::NodeOptions& options);

    private:
        void initializeParameter();

        void MarkersCallback(const objects_msgs::msg::ObjectArray::ConstSharedPtr& objects);

        std::string color;
        std::string label_fmt;
        std::vector<std::string> classes;

        rclcpp::Subscription<objects_msgs::msg::ObjectArray>::SharedPtr obj_sub_;
        rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;
    };
}//namespace objects2markers
