#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>
#include <tf2/transform_datatypes.h>
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>

#include <objects_msgs/msg/object_array.hpp>
#include <opencv2/opencv.hpp>

#include "../include/utils.hpp"

class DrawObjects3DNode : public rclcpp::Node {
public:
    DrawObjects3DNode() : Node("draw_objects3d") { 

        tf_buffer = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        tf_listener = std::make_shared<tf2_ros::TransformListener>(*tf_buffer);

        //Declare parameter for function
        this->declare_parameter<bool>("visualize", false);
        this->declare_parameter<bool>("approximate_sync", false);
        this->declare_parameter<bool>("rectified", false);
        this->declare_parameter<std::string>("color", "label");
        this->declare_parameter<std::string>("label_fmt", "{label} {score} {id}");
        this->declare_parameter<std::string>("camera_frame", "");
        this->declare_parameter<double>("font_scale", 1.0);
        this->declare_parameter<int>("line_width", 1);
        this->declare_parameter<int>("queue_size", 5);
        this->declare_parameter<std::vector<std::string>>("classes", std::vector<std::string>(10, "unknown"));

        //Declare topic name and getting these parameters
        this->declare_parameter<std::string>("sub_objects_topic_name", "/detection/objects3d");
        this->declare_parameter<std::string>("sub_image_topic_name", "/viz/image_tracks");
        this->declare_parameter<std::string>("sub_camera_info_topic_name", "/sensum/left/camera_info");
        this->declare_parameter<std::string>("pub_objects3d_visualisation_topic_name", "objects3d_vis_topic");

        std::string sub_objects_topic_name = this->get_parameter("sub_objects_topic_name").get_parameter_value().get<std::string>();
        std::string sub_image_topic_name = this->get_parameter("sub_image_topic_name").get_parameter_value().get<std::string>();
        std::string sub_camera_info_topic_name = this->get_parameter("sub_camera_info_topic_name").get_parameter_value().get<std::string>();
        std::string pub_objects3d_visualisation_topic_name = this->get_parameter("pub_objects3d_visualisation_topic_name").get_parameter_value().get<std::string>();

        image_sub = std::make_shared<message_filters::Subscriber<sensor_msgs::msg::Image>>(this, sub_image_topic_name);
        objects_sub = std::make_shared<message_filters::Subscriber<objects_msgs::msg::ObjectArray>>(this, sub_objects_topic_name);
        cam_sub = std::make_shared<message_filters::Subscriber<sensor_msgs::msg::CameraInfo>>(this, sub_camera_info_topic_name);
        objects_vis_pub = image_transport::create_publisher(this, pub_objects3d_visualisation_topic_name);
        
        int queue_size = this->get_parameter("queue_size").get_parameter_value().get<int>();
        bool visualize = this->get_parameter("visualize").get_parameter_value().get<bool>();

        sync_.reset(new message_filters::TimeSynchronizer<sensor_msgs::msg::CameraInfo, sensor_msgs::msg::Image, objects_msgs::msg::ObjectArray>(*cam_sub, *image_sub, *objects_sub, queue_size));
        sync_ = std::make_shared<message_filters::TimeSynchronizer<sensor_msgs::msg::CameraInfo, sensor_msgs::msg::Image, objects_msgs::msg::ObjectArray>>(*cam_sub, *image_sub, *objects_sub, queue_size);
        sync_->registerCallback(std::bind(&DrawObjects3DNode::combinedCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

private:
    std::shared_ptr<tf2_ros::Buffer> tf_buffer;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener;
    
    //Declaring variables for subscriber
    std::shared_ptr<message_filters::Subscriber<sensor_msgs::msg::CameraInfo>> cam_sub;
    std::shared_ptr<message_filters::Subscriber<sensor_msgs::msg::Image>> image_sub;
    std::shared_ptr<message_filters::Subscriber<objects_msgs::msg::ObjectArray>> objects_sub;
    std::shared_ptr<message_filters::TimeSynchronizer<sensor_msgs::msg::CameraInfo, sensor_msgs::msg::Image, objects_msgs::msg::ObjectArray>> sync_;
    
    //Declaring variables for publisher
    image_transport::Publisher objects_vis_pub;

void combinedCallback(const sensor_msgs::msg::CameraInfo::ConstSharedPtr &cam_info, 
                      const sensor_msgs::msg::Image::ConstSharedPtr &msg_image, 
                      const objects_msgs::msg::ObjectArray::ConstSharedPtr &msg_objects) {
    if(objects_vis_pub.getNumSubscribers() == 0){
        return;
    }
    else{
        sensor_msgs::msg::CameraInfo cam_info_ = *cam_info;
        rclcpp::Time msg_time(msg_objects->header.stamp);

        std::string color = this->get_parameter("color").get_parameter_value().get<std::string>();
        std::string label_fmt = this->get_parameter("label_fmt").get_parameter_value().get<std::string>();
        std::vector<std::string> classes = this->get_parameter("classes").get_parameter_value().get<std::vector<std::string>>();

        bool rectified =  this->get_parameter("rectified").get_parameter_value().get<bool>();
        bool visualize = this->get_parameter("visualize").get_parameter_value().get<bool>();
        int line_width =  this->get_parameter("line_width").get_parameter_value().get<int>();

        
        rclcpp::Time prev_time; 

        if (prev_time.nanoseconds() != 0 && prev_time > msg_time) {
            tf_buffer->clear();
            prev_time = msg_time;
        return;
        }
        
        std::string camera_frame_ = cam_info->header.frame_id;
        std::string camera_frame = this->get_parameter("camera_frame").get_parameter_value().get<std::string>();
        if (!camera_frame.empty()) {
            camera_frame_ = camera_frame;
        }
        
        geometry_msgs::msg::TransformStamped tf;
        auto cv_ptr = cv_bridge::toCvCopy(msg_image, "bgr8");

        try {
            tf = tf_buffer->lookupTransform(camera_frame_, msg_objects->header.frame_id, msg_objects->header.stamp);
            for (const auto &obj : msg_objects->objects) {
                draw_object3d(cv_ptr->image, obj, cam_info_, object_color(obj.label, obj.id, color), &tf, rectified, line_width);
            }

            auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", cv_ptr->image).toImageMsg();
            objects_vis_pub.publish(*msg);

            if (visualize) {
                cv::imshow(get_parameter("pub_objects3d_visualisation_topic_name").get_parameter_value().get<std::string>(), cv_ptr->image);
                cv::waitKey(1);
            }
        } 
        catch (const tf2::TransformException &ex) {
            RCLCPP_WARN(this->get_logger(), "tf lookup error: %s", ex.what());
            return;
        }
    }
}
};


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DrawObjects3DNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    cv::destroyAllWindows();
    return 0;
}