#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <objects_vis/utils.hpp>

namespace objects_vis{

    class DrawObjects : public rclcpp::Node {
    public:
        DrawObjects(const rclcpp::NodeOptions& options);

    private:
        void callback(
            const sensor_msgs::msg::Image::ConstSharedPtr &msg_image,
            const objects_msgs::msg::Object2DArray::ConstSharedPtr &msg_objects
        );

        std::shared_ptr<message_filters::Subscriber<sensor_msgs::msg::Image>> image_sub;
        std::shared_ptr<message_filters::Subscriber<objects_msgs::msg::Object2DArray>> objects_sub;
        std::shared_ptr<message_filters::TimeSynchronizer<sensor_msgs::msg::Image, objects_msgs::msg::Object2DArray>> sync_;
        image_transport::Publisher objects_vis_pub;

        std::string image_topic;
        std::string objects_topic;
        std::string pub_topic;
        
        std::string color;
        std::string label_fmt;

        std::vector<std::string> classes;

        double font_scale;
        int queue_size;

        bool visualize;
        bool approximate_sync;
    };
}//namecpase objects_vis
