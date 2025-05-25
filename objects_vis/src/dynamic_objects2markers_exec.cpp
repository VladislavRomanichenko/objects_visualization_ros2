#include <objects_vis/dynamic_objects2markers_node.hpp>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions node_options;
    auto node = std::make_shared<objects_vis::DynamicObjects2Markers>(node_options);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}