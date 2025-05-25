#include <objects_vis/draw_objects3d_node.hpp>

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions node_options;
    auto node = std::make_shared<objects_vis::DrawObjects3D>(node_options);
    rclcpp::spin(node);
    rclcpp::shutdown();
    cv::destroyAllWindows();
    return 0;
}