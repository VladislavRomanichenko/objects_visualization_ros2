#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>
//----------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
//----------------------------------------------------------
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
//----------------------------------------------------------
#include <random>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <optional>
#include <cmath>
#include <iostream>
#include <numeric>
#include <array>
//----------------CUSTOM MESSAGE----------------------------
#include "objects_msgs/msg/object2_d.hpp"
#include "objects_msgs/msg/object2_d_array.hpp"
//----------------FOR 3D OBJECTS----------------------------
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/quaternion.hpp>
#include <geometry_msgs/msg/transform.hpp>
#include <tf2/transform_datatypes.h>


//------------------------------------------------------------------------------------------------
//  #####  ####### #     # ####### ######     #    #          #     # ####### ### #        #####  
// #     # #       ##    # #       #     #   # #   #          #     #    #     #  #       #     # 
// #       #       # #   # #       #     #  #   #  #          #     #    #     #  #       #       
// #  #### #####   #  #  # #####   ######  #     # #          #     #    #     #  #        #####  
// #     # #       #   # # #       #   #   ####### #          #     #    #     #  #             # 
// #     # #       #    ## #       #    #  #     # #          #     #    #     #  #       #     # 
//  #####  ####### #     # ####### #     # #     # #######     #####     #    ### #######  #####  
//------------------------------------------------------------------------------------------------


struct Rect_ {
    int x, y, width, height;

    Rect_(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    cv::Point tl() { 
        return cv::Point(cvRound(x), cvRound(y)); 
        }
    cv::Point br() { 
        return cv::Point(cvRound(x + width), cvRound(y + height)); 
        }
};


cv::Vec3b random_color(int seed) {
  const int NCOLORS = 10;
  static cv::Vec3b COLOR_TABLE[NCOLORS] = {
      cv::Vec3b(180, 119, 31),   
      cv::Vec3b(14, 127, 255),   
      cv::Vec3b(44, 160, 44),    
      cv::Vec3b(40, 39, 214),    
      cv::Vec3b(189, 103, 148),  
      cv::Vec3b(75, 86, 140),    
      cv::Vec3b(194, 119, 227),  
      cv::Vec3b(127, 127, 127),  
      cv::Vec3b(34, 189, 188),   
      cv::Vec3b(207, 190, 23),   

  };
  return COLOR_TABLE[seed % NCOLORS];
}


cv::Vec3b object_color(objects_msgs::msg::Object2D object, std::string color){
    if(color == "id"){
        return random_color(object.id);
    }
    else if(color == "label"){
        return random_color(object.label);
    }
    else{
        return cv::Vec3b(0, 255, 0);
    }
}


std::unordered_map<std::string, std::string> get_fields_and_field_types() {
      return {
          {"id", "int"},
          {"label", "int"},
          {"x", "int"},
          {"y", "int"},
          {"width", "int"},   
          {"height", "int"},
      };
  }

std::string object_label(objects_msgs::msg::Object2D object, std::string label_fmt, std::vector<std::string> classes) {
    if (label_fmt.empty()) {
        return "";
    }

    std::unordered_map<std::string, std::string> obj_dict;

    std::stringstream label_ss;
    auto label = label_fmt;

    for (const auto& field : get_fields_and_field_types()) {
        if (field.first == "id") obj_dict["id"] = std::to_string(object.id);
        else if (field.first == "label") obj_dict["label"] = std::to_string(object.label);
        else if (field.first == "x") obj_dict["x"] = std::to_string(object.x);
        else if (field.first == "y") obj_dict["y"] = std::to_string(object.y);
        else if (field.first == "width") obj_dict["width"] = std::to_string(object.width);
        else if (field.first == "height") obj_dict["height"] = std::to_string(object.height);
    }

    if (label.find("{id}") != std::string::npos) {
        label_ss << object.id << " ";
    } 
    if (label.find("{label}") != std::string::npos) {
        label_ss << classes[object.label] << " ";
    }
    if (label.find("{score}") != std::string::npos) {
        
        label_ss << std::fixed << std::setprecision(2) << object.score << " ";
    }   

    return label_ss.str();
}


Rect_ object_rect(objects_msgs::msg::Object2D &object){
    return Rect_(object.x, object.y, object.width, object.height);
}


void drawRect(cv::Mat &image, cv::Point p0, cv::Point p1, cv::Vec3b color, std::string label, double font_scale){
    int font_type = cv::FONT_HERSHEY_PLAIN;
    int font_weight = cvRound(font_scale);
    int thickness = cvRound(font_weight * 2);
    int baseline = 0;

    cv::Vec3b text_color = cv::Vec3b(255, 255, 255);

    cv::Size text_size = cv::getTextSize(label, font_type, font_scale, font_weight, &baseline);
    int label_w = text_size.width + 2;
    int label_h = text_size.height + 2 * thickness;

    cv::Point text_org, label_p0, label_p1;
    if (p1.x + text_size.width <= image.cols) {
        text_org = cv::Point(p1.x + 2, p0.y + baseline + label_h / 2);
        label_p0 = cv::Point(p1.x, p0.y);
        label_p1 = cv::Point(label_p0.x + label_w, label_p0.y + label_h);
    } else {
        text_org = cv::Point(p0.x - text_size.width, p0.y + baseline + label_h / 2);
        label_p0 = cv::Point(p0.x - label_w, p0.y);
        label_p1 = cv::Point(label_p0.x + label_w, label_p0.y + label_h);
    }

    cv::rectangle(image, p0, p1, color, thickness);
    if (!label.empty()) {
        cv::rectangle(image, label_p0, label_p1, color, cv::FILLED);
        cv::rectangle(image, label_p0, label_p1, color, thickness);
        cv::putText(image, label, text_org, font_type, font_scale, text_color, font_weight, cv::LINE_AA);
    }    
}


void drawObject(cv::Mat &image, objects_msgs::msg::Object2D object, std::string color, std::string label, std::vector<std::string> classes, double font_scale){
    cv::Vec3b result_color = object_color(object, color);
    std::string result_label = object_label(object, label, classes);
    Rect_ rect = object_rect(object);
    drawRect(image, rect.tl(), rect.br(), result_color, result_label, font_scale);
}


//-------------------------------------------------------------
//  #####  ######     #     # ####### ### #        #####  
// #     # #     #    #     #    #     #  #       #     # 
//       # #     #    #     #    #     #  #       #       
//  #####  #     #    #     #    #     #  #        #####  
//       # #     #    #     #    #     #  #             # 
// #     # #     #    #     #    #     #  #       #     # 
//  #####  ######      #####     #    ### #######  #####  
//-------------------------------------------------------------


using namespace std;
using geometry_msgs::msg::Point;
using geometry_msgs::msg::Pose;
using geometry_msgs::msg::Quaternion;
using geometry_msgs::msg::Transform;
using sensor_msgs::msg::CameraInfo;

typedef Eigen::Matrix4d Matrix4;
typedef Eigen::Quaterniond Quaterniond;
typedef Eigen::Vector3d Vector3d;

Matrix4 Rt_from_tq(const Point &t, const Quaternion &q) {
    Matrix4 Rt = Matrix4::Identity();
    Quaterniond quat(q.w, q.x, q.y, q.z);
    Rt.block<3, 3>(0, 0) = quat.toRotationMatrix();
    Rt.block<3, 1>(0, 3) = Vector3d(t.x, t.y, t.z);
    return Rt;
}

Matrix4 Rt_from_Pose(const Pose &pose) {
    return Rt_from_tq(pose.position, pose.orientation);
}

Matrix4 Rt_from_Transform(const Transform &tf) {
    Point t;
    t.x = tf.translation.x;
    t.y = tf.translation.y;
    t.z = tf.translation.z;
    Quaternion q = tf.rotation;
    return Rt_from_tq(t, q);
}

Pose Pose_from_Rt(const Matrix4 &Rt) {
    Pose pose;
    Quaterniond quat(Rt.block<3, 3>(0, 0));
    pose.orientation.x = quat.x();
    pose.orientation.y = quat.y();
    pose.orientation.z = quat.z();
    pose.orientation.w = quat.w();
    pose.position.x = Rt(0, 3);
    pose.position.y = Rt(1, 3);
    pose.position.z = Rt(2, 3);
    return pose;
}

void transform_object(Pose &pose, const Transform &tf) {
    Matrix4 Rt_tf = Rt_from_Transform(tf);
    Matrix4 Rt_pose = Rt_from_Pose(pose);
    Matrix4 transformed_Rt = Rt_tf * Rt_pose;
    pose = Pose_from_Rt(transformed_Rt);
}

void set_object_yaw(Pose &pose, double yaw, bool camera_frame = false) {
    Quaterniond quat;
    if (camera_frame) {
        Eigen::Matrix3d R;
        R << -std::sin(yaw), -std::cos(yaw), 0.0,
             0.0, 0.0, -1.0,
             std::cos(yaw), -std::sin(yaw), 0.0;
        quat = Quaterniond(R);
    } else {
        quat = Quaterniond(Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()));
    }
    pose.orientation.x = quat.x();
    pose.orientation.y = quat.y();
    pose.orientation.z = quat.z();
    pose.orientation.w = quat.w();
}

double get_object_yaw(const Pose &pose, bool camera_frame = false) {
    Quaterniond quat(pose.orientation.w, pose.orientation.x, pose.orientation.y, pose.orientation.z);
    if (camera_frame) {
        Eigen::Matrix3d R = quat.toRotationMatrix();
        return std::atan2(-R(0, 0), -R(0, 1));
    } else {
        return std::atan2(pose.orientation.z, pose.orientation.w);
    }
}

std::vector<Eigen::Vector3d> object_points(const geometry_msgs::msg::Pose& pose, const geometry_msgs::msg::Vector3& size, const Matrix4& Rt = Matrix4::Identity()) {
    double dx = size.x / 2.0, dy = size.y / 2.0, dz = size.z / 2.0;
    Eigen::Matrix<double, 8, 4> pts;
    pts << -dx, -dy, -dz, 1,
            dx, -dy, -dz, 1,
            dx,  dy, -dz, 1,
           -dx,  dy, -dz, 1,
           -dx, -dy,  dz, 1,
            dx, -dy,  dz, 1,
            dx,  dy,  dz, 1,
           -dx,  dy,  dz, 1;
    Matrix4 Rt_pose = Rt_from_Pose(pose);
    Eigen::Matrix<double, 8, 4> transformed_pts = (Rt * Rt_pose * pts.transpose()).transpose();
    std::vector<Eigen::Vector3d> res;
    for (int i = 0; i < 8; ++i) {
        res.push_back(transformed_pts.row(i).head<3>());
    }
    return res;
}

std::array<std::pair<int, int>, 14> EDGES_INDICES = {{
    {0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 4}, {1, 5}, {2, 6},
    {3, 7}, {4, 5}, {5, 6}, {6, 7}, {7, 4}, {1, 6}, {2, 5}
}};

struct CameraInfoMatrices {
    Eigen::Matrix3d K, R;
    Eigen::VectorXd D;
    Eigen::Matrix<double, 3, 4> P;
};

CameraInfoMatrices cam_info_to_matrices(const CameraInfo &cam_info) {
    Eigen::Matrix3d K;
    std::copy(std::begin(cam_info.k), std::end(cam_info.k), K.data());
    Eigen::VectorXd D = Eigen::Map<const Eigen::VectorXd>(cam_info.d.data(), cam_info.d.size());
    Eigen::Matrix3d R;
    std::copy(std::begin(cam_info.r), std::end(cam_info.r), R.data());
    Eigen::Matrix<double, 3, 4> P;
    std::copy(std::begin(cam_info.p), std::end(cam_info.p), P.data());
    return {K, R, D, P};
}