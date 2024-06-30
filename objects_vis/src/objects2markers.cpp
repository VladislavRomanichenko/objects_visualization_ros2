#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <std_msgs/msg/color_rgba.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <objects_msgs/msg/object_array.hpp>

#include "../include/utils.hpp"

using namespace std::chrono_literals;

class Objects2Markers : public rclcpp::Node {
public:
    Objects2Markers() : Node("draw_markers") {

        //Declare parameter for function
        this->declare_parameter<std::string>("color", "label");
        this->declare_parameter<std::string>("label_fmt", "{label}");
        this->declare_parameter<std::vector<std::string>>("classes", std::vector<std::string>(10, "unknown"));
        
        color_ = this->get_parameter("color").as_string();
        label_fmt_ = this->get_parameter("label_fmt").as_string();
        classes_ = this->get_parameter("classes").as_string_array();

        obj_sub_ = this->create_subscription<objects_msgs::msg::ObjectArray>(
            "/detection/objects3d", rclcpp::QoS(10),
            [this](const objects_msgs::msg::ObjectArray::ConstSharedPtr msg) {
                this->MarkersCallback(msg);
            });

        marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("markers", 10);
    }

private:
    void MarkersCallback(const objects_msgs::msg::ObjectArray::ConstSharedPtr& objects) {
        if(marker_pub_->get_subscription_count() == 0){
            return;
        }
        else{
            visualization_msgs::msg::MarkerArray markers;
            visualization_msgs::msg::Marker delete_all;

            delete_all.action = visualization_msgs::msg::Marker::DELETEALL;
            markers.markers.push_back(delete_all);

            for (const auto& obj : objects->objects) {
                std::string label = object_label(obj.score, obj.label, obj.id, label_fmt_, classes_);
                std_msgs::msg::ColorRGBA color = to_ColorRGBA(object_color(obj.label, obj.id, color_));
                auto m = create_markers(obj, objects->header, color, label);
                markers.markers.insert(markers.markers.end(), m.begin(), m.end());
            }
            marker_pub_->publish(markers);
        }
    }

    std::string color_;
    std::string label_fmt_;
    std::vector<std::string> classes_;
    
    rclcpp::Subscription<objects_msgs::msg::ObjectArray>::SharedPtr obj_sub_;
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Objects2Markers>());
    rclcpp::shutdown();
    return 0;
}
