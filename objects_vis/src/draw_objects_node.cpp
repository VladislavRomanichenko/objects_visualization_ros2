#include <objects_vis/draw_objects_node.hpp>

namespace objects_vis{


    DrawObjects::DrawObjects(const rclcpp::NodeOptions &options)
      : rclcpp::Node("draw_objects", options)
    {
            //Declare parameter for function
            this->visualize = this->declare_parameter<bool>("visualize", false);
            this->approximate_sync = this->declare_parameter<bool>("approximate_sync", false);
            this->color = this->declare_parameter<std::string>("color", "label");
            this->label_fmt = this->declare_parameter<std::string>("label_fmt", "{label} {score} {id}");
            this->font_scale = this->declare_parameter<double>("font_scale", 1.0);
            this->queue_size = this->declare_parameter<int>("queue_size", 5);
            this->classes = this->declare_parameter<std::vector<std::string>>("classes", std::vector<std::string>(10, "unknown"));

            std::string image_topic = this->declare_parameter<std::string>("image_topic", "image");
            std::string objects_topic = this->declare_parameter<std::string>("objects_topic", "objects2d");
            std::string pub_topic = this->declare_parameter<std::string>("pub_topic", "image_objects");
        
            this->image_sub = std::make_shared<message_filters::Subscriber<sensor_msgs::msg::Image>>(this, image_topic);
            this->objects_sub = std::make_shared<message_filters::Subscriber<objects_msgs::msg::Object2DArray>>(this, objects_topic);
            this->objects_vis_pub = image_transport::create_publisher(this, pub_topic);

            //Synchronizing a custom message and an image message for Callback function
            this->sync_ = std::make_shared<message_filters::TimeSynchronizer<sensor_msgs::msg::Image, objects_msgs::msg::Object2DArray>>(*image_sub, *objects_sub, queue_size);
            this->sync_->registerCallback(std::bind(&DrawObjects::callback, this, std::placeholders::_1, std::placeholders::_2));
    }


    void DrawObjects::callback(const sensor_msgs::msg::Image::ConstSharedPtr &msg_image, const objects_msgs::msg::Object2DArray::ConstSharedPtr &msg_objects) {
        if(this->objects_vis_pub.getNumSubscribers() == 0){
            return;
        }
        else{
            try {
                auto cv_ptr = cv_bridge::toCvCopy(msg_image, "bgr8");
                for(const auto & object : msg_objects->objects){
                    drawObject(cv_ptr->image, object, this->color, this->label_fmt, this->classes, this->font_scale);
                }
                auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", cv_ptr->image).toImageMsg();
                this->objects_vis_pub.publish(*msg);

                if (this->visualize) {
                    cv::imshow(this->objects_vis_pub.getTopic(), cv_ptr->image);
                    cv::waitKey(1);
                }
            }
            catch (cv_bridge::Exception &e) {
                RCLCPP_ERROR(this->get_logger(), "Error: %s", e.what());
            }
        }
    }


}//namespace objects_vis


#include <rclcpp_components/register_node_macro.hpp>
/*
   Register the component with class_loader.
   This acts as a sort of entry point, allowing the component to be discoverable
   when its library is being loaded into a running process.
*/
RCLCPP_COMPONENTS_REGISTER_NODE(objects_vis::DrawObjects)
