#pragma once

#include <iostream>

#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2/transform_datatypes.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>

#include <objects_msgs/msg/object_array.hpp>
#include <opencv2/opencv.hpp>

#include <objects_vis/utils.hpp>

namespace objects_vis{

    class DrawObjects3D : public rclcpp::Node {
    public:
    DrawObjects3D(const rclcpp::NodeOptions& options);

    private:
        void callback(const sensor_msgs::msg::CameraInfo::ConstSharedPtr &cam_info,
                        const sensor_msgs::msg::Image::ConstSharedPtr &msg_image,
                        const objects_msgs::msg::ObjectArray::ConstSharedPtr &msg_objects);

        std::shared_ptr<tf2_ros::Buffer> tf_buffer;
        std::shared_ptr<tf2_ros::TransformListener> tf_listener;

        //Declaring variables for subscriber
        std::shared_ptr<message_filters::Subscriber<sensor_msgs::msg::CameraInfo>> cam_sub;
        std::shared_ptr<message_filters::Subscriber<sensor_msgs::msg::Image>> image_sub;
        std::shared_ptr<message_filters::Subscriber<objects_msgs::msg::ObjectArray>> objects_sub;
        std::shared_ptr<message_filters::TimeSynchronizer<sensor_msgs::msg::CameraInfo, sensor_msgs::msg::Image, objects_msgs::msg::ObjectArray>> sync_;

        //Declaring variables for publisher
        image_transport::Publisher objects_vis_pub;

        std::string image_topic;
        std::string objects3d_topic;
        std::string camera_info_topic;
        std::string pub_topic;

        std::string color;
        std::string label_fmt;
        std::string camera_frame;

        std::vector<std::string> classes;

        double font_scale;
        int queue_size;
        int line_width;

        bool rectified;
        bool visualize;
        bool approximate_sync;
    };
}//namespace objects_vis
