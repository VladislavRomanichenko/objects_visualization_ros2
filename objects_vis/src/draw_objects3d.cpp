#include "../include/draw_objects3d.hpp"

namespace draw_objects3d_cpp{


    DrawObjects3DNode::DrawObjects3DNode(const rclcpp::NodeOptions &options)
      : rclcpp::Node("draw_objects3d", options)
    {
        tf_buffer = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        tf_listener = std::make_shared<tf2_ros::TransformListener>(*tf_buffer);

        this->initializeParameter();

        //Declare topic name and getting these parameters
        this->declare_parameter<std::string>("sub_objects_topic_name", "/objects3d");
        this->declare_parameter<std::string>("sub_image_topic_name", "/image");
        this->declare_parameter<std::string>("sub_camera_info_topic_name", "/camera_info");
        this->declare_parameter<std::string>("pub_objects3d_visualisation_topic_name", "objects3d_vis_topic");
        
        std::string sub_objects_topic_name = this->get_parameter("sub_objects_topic_name").get_parameter_value().get<std::string>();
        std::string sub_image_topic_name = this->get_parameter("sub_image_topic_name").get_parameter_value().get<std::string>();
        std::string sub_camera_info_topic_name = this->get_parameter("sub_camera_info_topic_name").get_parameter_value().get<std::string>();
        std::string pub_objects3d_visualisation_topic_name = this->get_parameter("pub_objects3d_visualisation_topic_name").get_parameter_value().get<std::string>();
        
        this->image_sub = std::make_shared<message_filters::Subscriber<sensor_msgs::msg::Image>>(this, sub_image_topic_name);
        this->objects_sub = std::make_shared<message_filters::Subscriber<objects_msgs::msg::ObjectArray>>(this, sub_objects_topic_name);
        this->cam_sub = std::make_shared<message_filters::Subscriber<sensor_msgs::msg::CameraInfo>>(this, sub_camera_info_topic_name);
        this->objects_vis_pub = image_transport::create_publisher(this, pub_objects3d_visualisation_topic_name);
    
        //Synchronizing a custom message and an image message for Callback function
        this->sync_.reset(new message_filters::TimeSynchronizer<sensor_msgs::msg::CameraInfo, sensor_msgs::msg::Image, objects_msgs::msg::ObjectArray>(*cam_sub, *image_sub, *objects_sub, queue_size));
        this->sync_ = std::make_shared<message_filters::TimeSynchronizer<sensor_msgs::msg::CameraInfo, sensor_msgs::msg::Image, objects_msgs::msg::ObjectArray>>(*cam_sub, *image_sub, *objects_sub, queue_size);
        this->sync_->registerCallback(std::bind(&DrawObjects3DNode::combinedCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      }


    void DrawObjects3DNode::initializeParameter()
    {
        //Declare parameter for function
        this->visualize = this->declare_parameter<bool>("visualize", false);
        this->approximate_sync = this->declare_parameter<bool>("approximate_sync", false);
        this->rectified = this->declare_parameter<bool>("rectified", false);
        this->color = this->declare_parameter<std::string>("color", "label");
        this->label_fmt = this->declare_parameter<std::string>("label_fmt", "{label} {score} {id}");
        this->camera_frame = this->declare_parameter<std::string>("camera_frame", "");
        this->font_scale = this->declare_parameter<double>("font_scale", 1.0);
        this->line_width = this->declare_parameter<int>("line_width", 1);
        this->queue_size = this->declare_parameter<int>("queue_size", 5);
        this->classes = this->declare_parameter<std::vector<std::string>>("classes", std::vector<std::string>(10, "unknown"));
    }


    void DrawObjects3DNode::combinedCallback(const sensor_msgs::msg::CameraInfo::ConstSharedPtr &cam_info, 
                      const sensor_msgs::msg::Image::ConstSharedPtr &msg_image, 
                      const objects_msgs::msg::ObjectArray::ConstSharedPtr &msg_objects) 
    {
        if(objects_vis_pub.getNumSubscribers() == 0){
            return;
        }
        else{
            sensor_msgs::msg::CameraInfo cam_info_ = *cam_info;
            rclcpp::Time msg_time(msg_objects->header.stamp);

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
                    draw_object3d(cv_ptr->image, obj, cam_info_, object_color(obj.label, obj.id, this->color), &tf, this->rectified, this->line_width);
                }

                auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", cv_ptr->image).toImageMsg();
                objects_vis_pub.publish(*msg);

                if (this->visualize) {
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
}//namespace draw_objects3d_cpp

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions node_options;
    rclcpp::spin(std::make_shared<draw_objects3d_cpp::DrawObjects3DNode>(node_options));
    rclcpp::shutdown();
    cv::destroyAllWindows();
    return 0;
}

#include <rclcpp_components/register_node_macro.hpp>
/*
   Register the component with class_loader.
   This acts as a sort of entry point, allowing the component to be discoverable
   when its library is being loaded into a running process.
*/
RCLCPP_COMPONENTS_REGISTER_NODE(draw_objects3d_cpp::DrawObjects3DNode)