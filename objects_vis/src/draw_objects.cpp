#include "../include/draw_objects.hpp"

namespace draw_objects2d_cpp{


    ImageViewerNode::ImageViewerNode(const rclcpp::NodeOptions &options)
      : rclcpp::Node("draw_objects", options)
    {
            this->initializeParameter();
            //Declare topic name and getting these parameters
    
            this->declare_parameter<std::string>("sub_bboxes_topic_name", "/detection/objects");
            this->declare_parameter<std::string>("sub_image_topic_name", "/sensum/left/image_raw");
            this->declare_parameter<std::string>("pub_objects_visualisation_topic_name", "objects_vis_topic");

            std::string sub_bboxes_topic_name = this->get_parameter("sub_bboxes_topic_name").get_parameter_value().get<std::string>();
            std::string sub_image_topic_name = this->get_parameter("sub_image_topic_name").get_parameter_value().get<std::string>();
            std::string pub_objects_visualisation_topic_name = this->get_parameter("pub_objects_visualisation_topic_name").get_parameter_value().get<std::string>();
    

            this->image_sub = std::make_shared<message_filters::Subscriber<sensor_msgs::msg::Image>>(this, sub_image_topic_name);
            this->objects_sub = std::make_shared<message_filters::Subscriber<objects_msgs::msg::Object2DArray>>(this, sub_bboxes_topic_name);
            this->objects_vis_pub = image_transport::create_publisher(this, pub_objects_visualisation_topic_name);

            //Synchronizing a custom message and an image message for Callback function
            this->sync_ = std::make_shared<message_filters::TimeSynchronizer<sensor_msgs::msg::Image, objects_msgs::msg::Object2DArray>>(*image_sub, *objects_sub, queue_size);
            this->sync_->registerCallback(std::bind(&ImageViewerNode::imageCallback, this, std::placeholders::_1, std::placeholders::_2)); 
    }


    void ImageViewerNode::initializeParameter()
    {
            //Declare parameter for function
            this->visualize = this->declare_parameter<bool>("visualize", false);
            this->approximate_sync = this->declare_parameter<bool>("approximate_sync", false);
            this->color = this->declare_parameter<std::string>("color", "label");
            this->label_fmt = this->declare_parameter<std::string>("label_fmt", "{label} {score} {id}");
            this->font_scale = this->declare_parameter<double>("font_scale", 1.0);
            this->queue_size = this->declare_parameter<int>("queue_size", 5);
            this->classes = this->declare_parameter<std::vector<std::string>>("classes", std::vector<std::string>(10, "unknown"));
    }


    void ImageViewerNode::imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr &msg_image, const objects_msgs::msg::Object2DArray::ConstSharedPtr &msg_objects) {
        if(this->objects_vis_pub.getNumSubscribers() == 0){
            return;
        }
        else{
            try {
                auto cv_ptr = cv_bridge::toCvCopy(msg_image, "bgr8");
                for(const auto & object : msg_objects->objects){
                    //The function that visualizes each object is in ./utils.hpp
                    drawObject(cv_ptr->image, object, this->color, this->label_fmt, this->classes, this->font_scale);
                }
                auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", cv_ptr->image).toImageMsg();
                this->objects_vis_pub.publish(*msg);

                if (this->visualize) {
                    cv::imshow(get_parameter("pub_objects_visualisation_topic_name").get_parameter_value().get<std::string>(), cv_ptr->image);
                    cv::waitKey(1);
                }    
            } 
            catch (cv_bridge::Exception &e) {
                RCLCPP_ERROR(this->get_logger(), "Error: %s", e.what());
            }
        }
    }   
    
     
}//namespace draw_objects2d_cpp

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions node_options;
    rclcpp::spin(std::make_shared<draw_objects2d_cpp::ImageViewerNode>(node_options));
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
RCLCPP_COMPONENTS_REGISTER_NODE(draw_objects2d_cpp::ImageViewerNode)