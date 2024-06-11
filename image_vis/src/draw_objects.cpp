#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include "./utils.cpp"

class ImageViewerNode : public rclcpp::Node {
public:
    ImageViewerNode() : Node("draw_objects") {

        //Declare parameter for function
        this->declare_parameter<bool>("visualize", true);
        this->declare_parameter<std::string>("color", "label");
        this->declare_parameter<std::string>("label_fmt", "{label} {score} {id}");
        this->declare_parameter<double>("font_scale", 1.0);
        this->declare_parameter<int>("queue_size", 5);
        this->declare_parameter<std::vector<std::string>>("classes", std::vector<std::string>(10, "unknown"));
        
        //Declare topic name and getting these parameters
        this->declare_parameter<std::string>("sub_bboxes_topic_name", "/detection/objects");
        this->declare_parameter<std::string>("sub_image_topic_name", "/sensum/left/image_raw");
        this->declare_parameter<std::string>("pub_objects_visualisation_topic_name", "objects_vis_topic");
        
        std::string sub_bboxes_topic_name = this->get_parameter("sub_bboxes_topic_name").get_parameter_value().get<std::string>();
        std::string sub_image_topic_name = this->get_parameter("sub_image_topic_name").get_parameter_value().get<std::string>();
        std::string pub_objects_visualisation_topic_name = this->get_parameter("pub_objects_visualisation_topic_name").get_parameter_value().get<std::string>();
        
        int queue_size = this->get_parameter("queue_size").get_parameter_value().get<int>();

        image_sub = std::make_shared<message_filters::Subscriber<sensor_msgs::msg::Image>>(this, sub_image_topic_name);
        objects_sub = std::make_shared<message_filters::Subscriber<objects_msgs::msg::Object2DArray>>(this, sub_bboxes_topic_name);
        objects_vis_pub = image_transport::create_publisher(this, pub_objects_visualisation_topic_name);
        
        //Synchronizing a custom message and an image message for Callback function
        sync_ = std::make_shared<message_filters::TimeSynchronizer<sensor_msgs::msg::Image, objects_msgs::msg::Object2DArray>>(*image_sub, *objects_sub, queue_size);
        sync_->registerCallback(std::bind(&ImageViewerNode::imageCallback, this, std::placeholders::_1, std::placeholders::_2));
    }

private:
    
    //Declaring variables for subscriber
    std::shared_ptr<message_filters::Subscriber<sensor_msgs::msg::Image>> image_sub;
    std::shared_ptr<message_filters::Subscriber<objects_msgs::msg::Object2DArray>> objects_sub;
    std::shared_ptr<message_filters::TimeSynchronizer<sensor_msgs::msg::Image, objects_msgs::msg::Object2DArray>> sync_;
    
    //Declaring variables for publisher
    image_transport::Publisher objects_vis_pub;
    
    void imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr &msg_image, const objects_msgs::msg::Object2DArray::ConstSharedPtr &msg_objects) {
        
        std::string color = this->get_parameter("color").get_parameter_value().get<std::string>();
        std::string label_fmt = this->get_parameter("label_fmt").get_parameter_value().get<std::string>();
        double font_scale = this->get_parameter("font_scale").get_parameter_value().get<double>();
        std::vector<std::string> classes = this->get_parameter("classes").get_parameter_value().get<std::vector<std::string>>();
        bool visualize = this->get_parameter("visualize").get_parameter_value().get<bool>();

        try {
            auto cv_ptr = cv_bridge::toCvCopy(msg_image, "bgr8");
            for(const auto & object : msg_objects->objects){
                //The function that visualizes each object is in ./utils.hpp
                drawObject(cv_ptr->image, object, color, label_fmt, classes, font_scale);
            }
            auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", cv_ptr->image).toImageMsg();
            objects_vis_pub.publish(*msg);
            
            if (visualize) {
                cv::imshow(get_parameter("pub_objects_visualisation_topic_name").get_parameter_value().get<std::string>(), cv_ptr->image);
                cv::waitKey(1);
            }    
        } 
        catch (cv_bridge::Exception &e) {
            RCLCPP_ERROR(this->get_logger(), "Error: %s", e.what());
        }
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImageViewerNode>());
    rclcpp::shutdown();
    cv::destroyAllWindows();
    return 0;
}