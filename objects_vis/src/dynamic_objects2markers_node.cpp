#include <objects_vis/dynamic_objects2markers_node.hpp>

namespace objects_vis{
    void DynamicObjects2Markers::objects_callback(const objects_msgs::msg::DynamicObjectArray::ConstSharedPtr& objects)
    {
        if (marker_pub_->get_subscription_count() == 0) {
            return;
        }
    
        visualization_msgs::msg::MarkerArray markers;
        visualization_msgs::msg::Marker delete_all;

        delete_all.action = visualization_msgs::msg::Marker::DELETEALL;
        markers.markers.push_back(delete_all);
    
        for (const auto& obj : objects->objects) {
            std::string label = object_label(obj.object.score, obj.object.label, obj.object.id, this->label_fmt, this->classes);
            std_msgs::msg::ColorRGBA color = to_ColorRGBA(object_color(obj.object.label, obj.object.id, this->color));
            
            auto bbox_marker = create_markers(obj.object, objects->header, color, label);
            auto pred_marker = create_pred_marker(objects->header, obj, color);
            auto traj_marker = create_traj_marker(objects->header, obj, color);
            
            markers.markers.insert(markers.markers.end(), bbox_marker.begin(), bbox_marker.end());
            
            if (pred_marker.points.size() > 0) {
                markers.markers.push_back(pred_marker);
            }
            if (traj_marker.points.size() > 0) {
                markers.markers.push_back(traj_marker);
            }
        }
        marker_pub_->publish(markers);
    }


    DynamicObjects2Markers::DynamicObjects2Markers(const rclcpp::NodeOptions &options) 
        : Node("dynamic_objects2markers", options)
    {

        //Declare parameter for function
        color = this->declare_parameter<std::string>("color", "label");
        label_fmt =this->declare_parameter<std::string>("label_fmt", "{label}");
        classes = this->declare_parameter<std::vector<std::string>>("classes", std::vector<std::string>(10, "unknown"));

        obj_sub_ = this->create_subscription<objects_msgs::msg::DynamicObjectArray>(
            "dynamic_objects3d", rclcpp::QoS(10),
            [this](const objects_msgs::msg::DynamicObjectArray::ConstSharedPtr msg) {
                this->objects_callback(msg);
            });

        marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("dynamic_markers", 10);

    }
}//namespace objects_vis


#include <rclcpp_components/register_node_macro.hpp>
/*
   Register the component with class_loader.
   This acts as a sort of entry point, allowing the component to be discoverable
   when its library is being loaded into a running process.
*/
RCLCPP_COMPONENTS_REGISTER_NODE(objects_vis::DynamicObjects2Markers)
