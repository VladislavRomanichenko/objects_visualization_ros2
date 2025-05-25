#include <objects_vis/objects2markers_node.hpp>

namespace objects_vis{

    Objects2Markers::Objects2Markers(const rclcpp::NodeOptions &options)
        : rclcpp::Node("objects2markers", options)
    {
        //Declare parameter for function
        this->declare_parameter<std::string>("color", "label");
        this->declare_parameter<std::string>("label_fmt", "{label}");
        this->declare_parameter<std::vector<std::string>>("classes", std::vector<std::string>(10, "unknown"));

        color = this->get_parameter("color").as_string();
        label_fmt = this->get_parameter("label_fmt").as_string();
        classes = this->get_parameter("classes").as_string_array();

        obj_sub_ = this->create_subscription<objects_msgs::msg::ObjectArray>(
            "objects3d", rclcpp::QoS(10),
            [this](const objects_msgs::msg::ObjectArray::ConstSharedPtr msg) {
                this->MarkersCallback(msg);
            });

        marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("markers", 10);
    }


    void Objects2Markers::MarkersCallback(const objects_msgs::msg::ObjectArray::ConstSharedPtr& objects)
    {
        if(marker_pub_->get_subscription_count() == 0){
            return;
        }
        else{
            visualization_msgs::msg::MarkerArray markers;
            visualization_msgs::msg::Marker delete_all;

            delete_all.action = visualization_msgs::msg::Marker::DELETEALL;
            markers.markers.push_back(delete_all);

            for (const auto& obj : objects->objects) {
                std::string label = object_label(obj.score, obj.label, obj.id, this->label_fmt, this->classes);
                std_msgs::msg::ColorRGBA color = to_ColorRGBA(object_color(obj.label, obj.id, this->color));
                auto m = create_markers(obj, objects->header, color, label);
                markers.markers.insert(markers.markers.end(), m.begin(), m.end());
            }
            marker_pub_->publish(markers);
        }
    }
}//namespace objects_vis


#include <rclcpp_components/register_node_macro.hpp>
/*
   Register the component with class_loader.
   This acts as a sort of entry point, allowing the component to be discoverable
   when its library is being loaded into a running process.
*/
RCLCPP_COMPONENTS_REGISTER_NODE(objects_vis::Objects2Markers)
