#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
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

#include "./geometry.cpp"

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

template<typename ObjectsType> cv::Vec3b object_color(ObjectsType object, std::string color){
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


void draw_object3d(cv::Mat &img,
                   const objects_msgs::msg::Object &obj,
                   const sensor_msgs::msg::CameraInfo &cam_info,
                   const cv::Vec3b &color,
                   const geometry_msgs::msg::Transform *tf = nullptr,
                   bool rectified = false) {
    Eigen::Matrix4d Rt = Eigen::Matrix4d::Identity();
    if (tf) {
        Rt = Rt_from_Transform(*tf);
    }
    std::vector<Eigen::Vector3d> pts = object_points(obj, Rt);
    
    bool skip_object = false;
    for (const auto &pt : pts) {
        if (pt.z() <= 0) {
            skip_object = true;
            break;
        }
    }
    if (skip_object) return;

    CameraInfoMatrices r = cam_info_to_matrices(cam_info);
    Eigen::Matrix3d K;
    Eigen::VectorXd D;
    cv::Mat rvec, tvec, K_cv, D_cv;

    if (rectified) {
        K = r.P.leftCols<3>();
        D = Eigen::VectorXd::Zero(5);
        rvec = cv::Mat::zeros(3, 1, CV_64F);
        tvec = (cv::Mat_<double>(3, 1) << r.P(0, 3) / r.P(0, 0), r.P(1, 3) / r.P(1, 1), 0);
    } else {
        K = r.K;
        D = r.D;
        cv::Rodrigues(eigenToCvMat(r.R.inverse()), rvec);
        tvec = cv::Mat::zeros(3, 1, CV_64F);
    }

    K_cv = eigenToCvMat(K);
    D_cv = cv::Mat(D.size(), 1, CV_64F);
    for (int i = 0; i < D.size(); ++i) {
        D_cv.at<double>(i) = D(i);
    }

    cv::Mat pts_mat = eigenVectorsToCvMat(pts);

    std::vector<cv::Point2d> ipts;
    cv::projectPoints(pts_mat, rvec, tvec, K_cv, D_cv, ipts);

    for (const auto &edge : EDGES_INDICES) {
    if (edge.first >= static_cast<int>(ipts.size()) || edge.second >= static_cast<int>(ipts.size())) continue;  // Ensure index bounds
    cv::Point p1(static_cast<int>(ipts[edge.first].x), static_cast<int>(ipts[edge.first].y));
    cv::Point p2(static_cast<int>(ipts[edge.second].x), static_cast<int>(ipts[edge.second].y));
    cv::line(img, p1, p2, color, 1, cv::LINE_AA);
    } 
}