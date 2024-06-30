#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include "./utils.hpp"

class ImageViewerNode : public rclcpp::Node {
public:
    ImageViewerNode();

private:
    std::shared_ptr<message_filters::Subscriber<sensor_msgs::msg::Image>> image_sub;
    std::shared_ptr<message_filters::Subscriber<objects_msgs::msg::Object2DArray>> objects_sub;
    std::shared_ptr<message_filters::TimeSynchronizer<sensor_msgs::msg::Image, objects_msgs::msg::Object2DArray>> sync_;
    image_transport::Publisher objects_vis_pub;

    void imageCallback(
        const sensor_msgs::msg::Image::ConstSharedPtr &msg_image,
        const objects_msgs::msg::Object2DArray::ConstSharedPtr &msg_objects
    );
};

