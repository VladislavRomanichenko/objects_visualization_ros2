#pragma once

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <std_msgs/msg/color_rgba.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <objects_msgs/msg/object_array.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <objects_msgs/msg/dynamic_object.hpp>
#include <objects_msgs/msg/dynamic_object_array.hpp>

#include <memory>
#include <string>
#include <vector>

#include <objects_vis/utils.hpp>

namespace objects_vis
{
    class DynamicObjects2Markers : public rclcpp::Node
    {
    public:
        explicit DynamicObjects2Markers(const rclcpp::NodeOptions& options);

    private:
        void objects_callback(const objects_msgs::msg::DynamicObjectArray::ConstSharedPtr& objects);

        std::string color;
        std::string label_fmt;
        std::vector<std::string> classes;

        rclcpp::Subscription<objects_msgs::msg::DynamicObjectArray>::SharedPtr obj_sub_;
        rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;
    };

}  // namespace objects_vis