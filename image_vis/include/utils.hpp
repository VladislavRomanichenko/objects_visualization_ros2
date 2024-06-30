#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>

#include <geometry_msgs/msg/transform_stamped.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/quaternion.hpp>
#include <geometry_msgs/msg/transform.hpp>

#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <tf2/transform_datatypes.h>
#include <sensor_msgs/msg/camera_info.hpp>
#include <std_msgs/msg/color_rgba.hpp>
//----------------------------------------------------------
#include <random>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <memory>
#include <optional>
#include <cmath>
#include <iostream>
#include <numeric>
#include <array>
#include <algorithm>
//----------------CUSTOM MESSAGE----------------------------
#include "objects_msgs/msg/object2_d.hpp"
#include "objects_msgs/msg/object2_d_array.hpp"
#include "objects_msgs/msg/object.hpp"
#include "objects_msgs/msg/object_array.hpp"

typedef Eigen::Matrix4d Matrix4;
typedef Eigen::Quaterniond Quaterniond;
typedef Eigen::Vector3d Vector3d;

struct CameraInfoMatrices {
    Eigen::Matrix3d K;
    Eigen::VectorXd D;
    Eigen::Matrix3d R;
    Eigen::Matrix<double, 3, 4> P;
};

struct Rect_ {
    int x, y, width, height;

    Rect_(int x, int y, int width, int height);
    cv::Point tl();
    cv::Point br();
};

static const std::array<std::pair<int, int>, 14> EDGES_INDICES = {{
    {0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 4}, {1, 5}, {2, 6},
    {3, 7}, {4, 5}, {5, 6}, {6, 7}, {7, 4}, {1, 6}, {2, 5}
}};

Eigen::Matrix4d Rt_from_tq(const geometry_msgs::msg::Point &t, const geometry_msgs::msg::Quaternion &q);

Matrix4 Rt_from_Pose(const geometry_msgs::msg::Pose &pose);

Eigen::Matrix4d Rt_from_Transform(const geometry_msgs::msg::TransformStamped &tf_stamped);

geometry_msgs::msg::Pose Pose_from_Rt(const Matrix4 &Rt);

void transform_object(objects_msgs::msg::Object object, const geometry_msgs::msg::TransformStamped &tf);

void set_object_yaw(objects_msgs::msg::Object object, double yaw, bool camera_frame = false);

double get_object_yaw(objects_msgs::msg::Object object, bool camera_frame = false);

std::vector<Eigen::Vector3d> object_points(objects_msgs::msg::Object object, const Matrix4& Rt = Matrix4::Identity());

cv::Mat eigenToCvMat(const Eigen::MatrixXd& mat);

cv::Mat eigenVectorsToCvMat(const std::vector<Eigen::Vector3d>& eigenVecs);

CameraInfoMatrices cam_info_to_matrices(const sensor_msgs::msg::CameraInfo& cam_info);

cv::Vec3b random_color(int seed);

cv::Vec3b object_color(int32_t label, int32_t id, std::string color);

std::unordered_map<std::string, std::string> get_fields_and_field_types();

std::string object_label(float score, int32_t label_object, int32_t id, std::string label_fmt, std::vector<std::string> classes);

Rect_ object_rect(objects_msgs::msg::Object2D &object);

void drawRect(cv::Mat &image, 
                cv::Point p0, 
                cv::Point p1, 
                cv::Vec3b color, 
                std::string label, 
                double font_scale);

void drawObject(cv::Mat &image,
                objects_msgs::msg::Object2D object, 
                std::string color, 
                std::string label_fmt, 
                std::vector<std::string> classes, 
                double font_scale);

void draw_object3d(cv::Mat &img,
                   const objects_msgs::msg::Object &obj,
                   const sensor_msgs::msg::CameraInfo &cam_info,
                   const cv::Vec3b &color,
                   const geometry_msgs::msg::TransformStamped *tf = nullptr,
                   bool rectified = false,
                   int line_width = 1);

std_msgs::msg::ColorRGBA to_ColorRGBA(const cv::Vec3b& arr);

std::vector<visualization_msgs::msg::Marker> create_markers(
    const objects_msgs::msg::Object &obj,
    const std_msgs::msg::Header &header,
    const std_msgs::msg::ColorRGBA &color,
    const std::string &label
);

extern const visualization_msgs::msg::Marker DELETE_ALL_MARKERS;