#include <objects_vis/draw_objects_node.hpp>

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions node_options;
    auto node = std::make_shared<objects_vis::DrawObjects>(node_options);
    rclcpp::spin(node);
    rclcpp::shutdown();
    cv::destroyAllWindows();
    return 0;
}