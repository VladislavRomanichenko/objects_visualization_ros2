#include <memory>
#include <random>
#include <vector>

#include <opencv2/opencv.hpp>
#include <rclcpp/rclcpp.hpp>
#include <cv_bridge/cv_bridge.h>

#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/quaternion.hpp>
#include <geometry_msgs/msg/vector3.hpp>

#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/header.hpp>

#include <objects_msgs/msg/object.hpp>
#include <objects_msgs/msg/object2_d.hpp>
#include <objects_msgs/msg/object2_d_array.hpp>
#include <objects_msgs/msg/object_array.hpp>

#include <objects_vis/utils.hpp>

class RandomObjectPublisher : public rclcpp::Node {
public:
    RandomObjectPublisher() : Node("publish_random_objects") {
        im_width_ = this->declare_parameter<int>("im_width", 640); 
        im_height_ = this->declare_parameter<int>("im_height", 480);
        fov_ = this->declare_parameter<double>("fov", 90.0);
        nclasses_ = this->declare_parameter<int>("nclasses", 5);
        nobjects_ = this->declare_parameter<int>("nobjects", 3);
        frame_id_ = this->declare_parameter<std::string>("frame_id", "random_objects");
        
        double rate = this->declare_parameter<double>("rate", 1.0);
        double f = im_width_ / (2 * std::tan(M_PI * fov_ / 360.0));  
        
        K_ = cv::Mat(3, 3, CV_64F);
        K_.at<double>(0, 0) = f;
        K_.at<double>(0, 1) = 0;
        K_.at<double>(0, 2) = (im_width_ - 1) / 2.0;
        K_.at<double>(1, 0) = 0;
        K_.at<double>(1, 1) = f;
        K_.at<double>(1, 2) = (im_height_ - 1) / 2.0;
        K_.at<double>(2, 0) = 0;
        K_.at<double>(2, 1) = 0;
        K_.at<double>(2, 2) = 1;

        pub_image_ = this->create_publisher<sensor_msgs::msg::Image>("image", 1);
        pub_cam_info_ = this->create_publisher<sensor_msgs::msg::CameraInfo>("camera_info", 1);
        pub_objects2d_ = this->create_publisher<objects_msgs::msg::Object2DArray>("objects2d", 1);
        pub_objects3d_ = this->create_publisher<objects_msgs::msg::ObjectArray>("objects3d", 1);

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(static_cast<int>(1000.0 / rate)),
            std::bind(&RandomObjectPublisher::publish_data, this));
    }

private:
void publish_data() {
    auto header = std_msgs::msg::Header();
    header.frame_id = frame_id_;
    header.stamp = this->get_clock()->now();

    auto objects2d_msg = objects_msgs::msg::Object2DArray();
    objects2d_msg.header = header;

    auto objects3d_msg = objects_msgs::msg::ObjectArray();
    objects3d_msg.header = header;

    auto cam_info_msg = sensor_msgs::msg::CameraInfo();
    cam_info_msg.header = header;
    for (int i = 0; i < 9; ++i) {
        cam_info_msg.k[i] = K_.at<double>(i / 3, i % 3);
    }
    cam_info_msg.d = {0.0, 0.0, 0.0, 0.0, 0.0};
    cv::Mat P = cv::Mat::zeros(3, 4, CV_64F);
    K_.copyTo(P(cv::Rect(0, 0, 3, 3)));
    for (int i = 0; i < 12; ++i) {
        cam_info_msg.p[i] = P.at<double>(i / 4, i % 4);
    }
    cv::Mat R = cv::Mat::eye(3, 3, CV_64F);
    for (int i = 0; i < 9; ++i) {
        cam_info_msg.r[i] = R.at<double>(i / 3, i % 3);
    }

    cv::Mat image(im_height_, im_width_, CV_8UC3, cv::Scalar(255, 255, 255));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> label_dist(0, nclasses_ - 1);
    std::uniform_real_distribution<> score_dist(0.0, 1.0);
    std::uniform_real_distribution<> x_dist(-10.0, 10.0);
    std::uniform_real_distribution<> y_dist(-10.0, 10.0);
    std::uniform_real_distribution<> z_dist(10.0, 20.0);
    std::uniform_real_distribution<> size_dist(0.2, 1.0);

    for (int id = 0; id < nobjects_; ++id) {
        int label = label_dist(gen);
        float score = score_dist(gen);

        double x = x_dist(gen);
        double y = y_dist(gen);
        double z = z_dist(gen);
        double dx = size_dist(gen);
        double dy = size_dist(gen);
        double dz = size_dist(gen);

        auto pose = geometry_msgs::msg::Pose();
        pose.position.x = x;
        pose.position.y = y;
        pose.position.z = z;
        pose.orientation.w = 1.0;

        auto size = geometry_msgs::msg::Vector3();
        size.x = 2 * dx;
        size.y = 2 * dy;
        size.z = 2 * dz;

        auto obj3d = objects_msgs::msg::Object();
        obj3d.id = id;
        obj3d.label = label;
        obj3d.score = score;
        obj3d.pose = pose;
        obj3d.size = size;
        objects3d_msg.objects.push_back(obj3d);

        auto eigen_pts = object_points(obj3d);
        if (eigen_pts.empty()) {
            RCLCPP_WARN(this->get_logger(), "Object %d: No points returned by object_points", id);
            continue;
        }

        cv::Mat pts(eigen_pts.size(), 3, CV_64F);
        for (size_t i = 0; i < eigen_pts.size(); ++i) {
            pts.at<double>(i, 0) = eigen_pts[i].x();
            pts.at<double>(i, 1) = eigen_pts[i].y();
            pts.at<double>(i, 2) = eigen_pts[i].z();
        }

        cv::Mat rvec = cv::Mat::zeros(3, 1, CV_64F);
        cv::Mat tvec = cv::Mat::zeros(3, 1, CV_64F);
        cv::Mat dist_coeffs = cv::Mat::zeros(5, 1, CV_64F);
        cv::Mat ipts;
        cv::projectPoints(pts, rvec, tvec, K_, dist_coeffs, ipts);
        ipts = ipts.reshape(1, ipts.rows);

        double min_u, max_u, min_v, max_v;
        cv::minMaxLoc(ipts.col(0), &min_u, &max_u);
        cv::minMaxLoc(ipts.col(1), &min_v, &max_v);

        int border = 3;
        int u0 = std::max(0, static_cast<int>(std::floor(min_u)) - border);
        int u1 = std::min(im_width_ - 1, static_cast<int>(std::ceil(max_u)) + border);
        int v0 = std::max(0, static_cast<int>(std::floor(min_v)) - border);
        int v1 = std::min(im_height_ - 1, static_cast<int>(std::ceil(max_v)) + border);

        if (u0 >= u1 || v0 >= v1) {
            RCLCPP_WARN(this->get_logger(), "Object %d: Invalid bbox [%d, %d, %d, %d]", id, u0, u1, v0, v1);
            continue;
        }

        auto obj2d = objects_msgs::msg::Object2D();
        obj2d.id = id;
        obj2d.label = label;
        obj2d.score = score;
        obj2d.x = u0;
        obj2d.y = v0;
        obj2d.width = u1 - u0;
        obj2d.height = v1 - v0;
        objects2d_msg.objects.push_back(obj2d);

        // Рисуем объект
        cv::Scalar color = random_color(id); // Предполагаем, что random_color возвращает 0-1
        cv::Vec3b color_vec(static_cast<uchar>(color[0] * 255),
                            static_cast<uchar>(color[1] * 255),
                            static_cast<uchar>(color[2] * 255));
        draw_object3d(image, obj3d, cam_info_msg, color_vec, nullptr, false, 2);
    }

    // Публикуем сообщения
    sensor_msgs::msg::Image::SharedPtr image_msg = cv_bridge::CvImage(header, "bgr8", image).toImageMsg();
    pub_image_->publish(*image_msg);
    pub_objects2d_->publish(objects2d_msg);
    pub_objects3d_->publish(objects3d_msg);
    pub_cam_info_->publish(cam_info_msg);
}

int im_width_, im_height_;
double fov_;
int nclasses_, nobjects_;
std::string frame_id_;
cv::Mat K_;
rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_image_;
rclcpp::Publisher<sensor_msgs::msg::CameraInfo>::SharedPtr pub_cam_info_;
rclcpp::Publisher<objects_msgs::msg::Object2DArray>::SharedPtr pub_objects2d_;
rclcpp::Publisher<objects_msgs::msg::ObjectArray>::SharedPtr pub_objects3d_;
rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RandomObjectPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}