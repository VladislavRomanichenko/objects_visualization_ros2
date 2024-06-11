#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
//----------------------------------------------------------
#include <vector>
//----------------CUSTOM MESSAGE----------------------------
#include "objects_msgs/msg/object.hpp"
#include "objects_msgs/msg/object_array.hpp"
//----------------FOR 3D OBJECTS----------------------------
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/quaternion.hpp>
#include <geometry_msgs/msg/transform.hpp>
#include <tf2/transform_datatypes.h>
#include <sensor_msgs/msg/camera_info.hpp>

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


void transform_object(objects_msgs::msg::Object object, const Transform &tf) {
    Matrix4 Rt_tf = Rt_from_Transform(tf);
    Matrix4 Rt_pose = Rt_from_Pose(object.pose);
    Matrix4 transformed_Rt = Rt_tf * Rt_pose;
    object.pose = Pose_from_Rt(transformed_Rt);
}


void set_object_yaw(objects_msgs::msg::Object object, double yaw, bool camera_frame = false) {
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
    object.pose.orientation.x = quat.x();
    object.pose.orientation.y = quat.y();
    object.pose.orientation.z = quat.z();
    object.pose.orientation.w = quat.w();
}


double get_object_yaw(objects_msgs::msg::Object object, bool camera_frame = false) {
    Quaterniond quat(object.pose.orientation.w, object.pose.orientation.x, object.pose.orientation.y, object.pose.orientation.z);
    if (camera_frame) {
        Eigen::Matrix3d R = quat.toRotationMatrix();
        return std::atan2(-R(0, 0), -R(0, 1));
    } else {
        return std::atan2(object.pose.orientation.z, object.pose.orientation.w);
    }
}


std::vector<Eigen::Vector3d> object_points(objects_msgs::msg::Object object, const Matrix4& Rt = Matrix4::Identity()) {
    double dx = object.size.x / 2.0, dy = object.size.y / 2.0, dz = object.size.z / 2.0;
    Eigen::Matrix<double, 8, 4> pts;
    pts << -dx, -dy, -dz, 1,
            dx, -dy, -dz, 1,
            dx,  dy, -dz, 1,
           -dx,  dy, -dz, 1,
           -dx, -dy,  dz, 1,
            dx, -dy,  dz, 1,
            dx,  dy,  dz, 1,
           -dx,  dy,  dz, 1;
    Matrix4 Rt_pose = Rt_from_Pose(object.pose);
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


cv::Mat eigenToCvMat(const Eigen::MatrixXd& mat) {
    cv::Mat cvMat(mat.rows(), mat.cols(), CV_64F);
    for (int i = 0; i < mat.rows(); ++i) {
        for (int j = 0; j < mat.cols(); ++j) {
            cvMat.at<double>(i, j) = mat(i, j);
        }
    }
    return cvMat;
}

cv::Mat eigenVectorsToCvMat(const std::vector<Eigen::Vector3d>& eigenVecs) {
    cv::Mat cvMat(static_cast<int>(eigenVecs.size()), 3, CV_64F);
    for (size_t i = 0; i < eigenVecs.size(); ++i) {
        cvMat.at<double>(static_cast<int>(i), 0) = eigenVecs[i](0);
        cvMat.at<double>(static_cast<int>(i), 1) = eigenVecs[i](1);
        cvMat.at<double>(static_cast<int>(i), 2) = eigenVecs[i](2);
    }
    return cvMat;
}


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