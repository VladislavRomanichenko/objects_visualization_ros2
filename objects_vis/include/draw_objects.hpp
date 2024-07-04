#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include "../include/utils.hpp"

namespace draw_objects2d_cpp{

    class ImageViewerNode : public rclcpp::Node {
    public:
        ImageViewerNode(const rclcpp::NodeOptions& options);

    private:
        void initializeParameter();
        
        void imageCallback(
            const sensor_msgs::msg::Image::ConstSharedPtr &msg_image,
            const objects_msgs::msg::Object2DArray::ConstSharedPtr &msg_objects
        );

        std::shared_ptr<message_filters::Subscriber<sensor_msgs::msg::Image>> image_sub;
        std::shared_ptr<message_filters::Subscriber<objects_msgs::msg::Object2DArray>> objects_sub;
        std::shared_ptr<message_filters::TimeSynchronizer<sensor_msgs::msg::Image, objects_msgs::msg::Object2DArray>> sync_;
        image_transport::Publisher objects_vis_pub;

        std::string sub_bboxes_topic_name;
        std::string sub_image_topic_name;
        std::string pub_objects_visualisation_topic_name;
        std::string color;
        std::string label_fmt;

        std::vector<std::string> classes;

        double font_scale;
        int queue_size;

        bool visualize;
        bool approximate_sync;
    };
}

