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
#include <objects_msgs/msg/object2_d.hpp>
#include <objects_msgs/msg/object2_d_array.hpp>
#include <objects_msgs/msg/object.hpp>
#include <objects_msgs/msg/object_array.hpp>
#include <objects_msgs/msg/dynamic_object.hpp>
#include <objects_msgs/msg/dynamic_object_array.hpp>

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


/**
 * @brief Constructs a 4x4 transformation matrix from translation and quaternion.
 *
 * @param t The translation component as geometry_msgs::msg::Point.
 * @param q The rotation component as geometry_msgs::msg::Quaternion.
 * @return Eigen::Matrix4d The resulting 4x4 transformation matrix.
 */
Eigen::Matrix4d Rt_from_tq(const geometry_msgs::msg::Point &t, const geometry_msgs::msg::Quaternion &q);


/**
 * @brief Constructs a 4x4 transformation matrix from the pose.
 *
 * @param pose The input pose as geometry_msgs::msg::Pose.
 * @return Matrix4 The resulting 4x4 transformation matrix.
 */
Matrix4 Rt_from_Pose(const geometry_msgs::msg::Pose &pose);


/**
 * @brief Constructs a 4x4 transformation matrix from a TransformStamped message.
 *
 * @param tf_stamped The TransformStamped message containing transform information.
 * @return Eigen::Matrix4d The resulting 4x4 transformation matrix.
 */
Eigen::Matrix4d Rt_from_Transform(const geometry_msgs::msg::TransformStamped &tf_stamped);


/**
 * @brief Constructs a Pose from a 4x4 transformation matrix.
 *
 * @param Rt The input 4x4 transformation matrix.
 * @return geometry_msgs::msg::Pose The resulting pose.
 */
geometry_msgs::msg::Pose Pose_from_Rt(const Matrix4 &Rt);


/**
 * @brief Transforms an object by applying a given transformation.
 *
 * @param object The object to be transformed as objects_msgs::msg::Object.
 * @param tf The transformation to be applied as geometry_msgs::msg::TransformStamped.
 */
void transform_object(objects_msgs::msg::Object object, const geometry_msgs::msg::TransformStamped &tf);


/**
 * @brief Sets the yaw of an object.
 *
 * @param object The object whose yaw is to be set as objects_msgs::msg::Object.
 * @param yaw The desired yaw angle.
 * @param camera_frame A flag indicating if the frame is that of a camera.
 */
void set_object_yaw(objects_msgs::msg::Object object, double yaw, bool camera_frame = false);


/**
 * @brief Gets the yaw of an object.
 *
 * @param object The object whose yaw is to be computed as objects_msgs::msg::Object.
 * @param camera_frame A flag indicating if the frame is that of a camera.
 * @return double The computed yaw angle.
 */
double get_object_yaw(objects_msgs::msg::Object object, bool camera_frame = false);


/**
 * @brief Generates a vector of 3D points representing the corners of a given object after applying a transformation.
 *
 * @param object The object whose points need to be generated.
 * @param Rt The transformation matrix to apply to the object.
 * @return std::vector<Eigen::Vector3d> A vector of 3D points representing the corners of the object.
 */
std::vector<Eigen::Vector3d> object_points(objects_msgs::msg::Object object, const Matrix4& Rt = Matrix4::Identity());


/**
 * @brief Converts an Eigen matrix to an OpenCV matrix.
 *
 * @param mat The Eigen matrix to be converted.
 * @return cv::Mat The resulting OpenCV matrix.
 */
cv::Mat eigenToCvMat(const Eigen::MatrixXd& mat);


/**
 * @brief Converts a vector of Eigen 3D vectors to an OpenCV matrix.
 *
 * @param eigenVecs The vector of Eigen 3D vectors to be converted.
 * @return cv::Mat The resulting OpenCV matrix.
 */
cv::Mat eigenVectorsToCvMat(const std::vector<Eigen::Vector3d>& eigenVecs);


/**
 * @brief Converts a CameraInfo message with information from the camera into a set of custom matrices.
 *
 * @param cam_info CameraInfo message.
 * @return CameraInfoMatrices The resulting structure containing the camera's internal and external matrices.
 */
CameraInfoMatrices cam_info_to_matrices(const sensor_msgs::msg::CameraInfo& cam_info);


/**
 * @brief Generates a random color based on a seed value.
 *
 * @param seed An integer seed value to determine the color.
 * @return cv::Vec3b A BGR color vector.
 */
cv::Vec3b random_color(int seed);

/**
 * @brief Determines the color for an object based on its label or ID.
 *
 * @param label An integer representing the object's label.
 * @param id An integer representing the object's ID.
 * @param color A string indicating whether to use "id" or "label" for color selection.
 * @return cv::Vec3b A BGR color vector.
 */
cv::Vec3b object_color(int32_t label, int32_t id, std::string color);


/**
 * @brief Generates a label for an object based on format and attributes.
 *
 * @param score A float representing the object's score.
 * @param label_object An integer representing the object's label.
 * @param id An integer representing the object's ID.
 * @param label_fmt A string indicating the label format.
 * @param classes A vector of class names.
 * @return std::string The formatted object label.
 */
std::string object_label(float score, int32_t label_object, int32_t id, const std::string& label_fmt, const std::vector<std::string>& classes);


/**
 * @brief Converts an object of type objects_msgs::msg::Object2D to a Rect_.
 *
 * @param object A reference to an Object2D message.
 * @return Rect_ A rectangle corresponding to the given object.
 */
Rect_ object_rect(objects_msgs::msg::Object2D &object);


/**
 * @brief Draws a rectangle and an optional label on an image.
 *
 * @param image A reference to the image on which to draw.
 * @param p0 The top-left point of the rectangle.
 * @param p1 The bottom-right point of the rectangle.
 * @param color The color of the rectangle.
 * @param label A string label to be drawn inside the rectangle.
 * @param font_scale A double representing the font scale.
 */
void drawRect(cv::Mat &image,
                cv::Point p0,
                cv::Point p1,
                cv::Vec3b color,
                std::string label,
                double font_scale);


/**
 * @brief Draws a 2D object on an image.
 *
 * @param image The image on which to draw the object.
 * @param object The 2D object to draw, represented by its properties.
 * @param color The color for drawing the object.
 * @param label_fmt The format of the label to be displayed.
 * @param classes A vector containing the classes of objects.
 * @param font_scale The scale of the font used for the label.
 */
void drawObject(cv::Mat &image,
                objects_msgs::msg::Object2D object,
                std::string color,
                std::string label_fmt,
                std::vector<std::string> classes,
                double font_scale);


/**
 * @brief Draws a 3D object on an image using camera and transformation information.
 *
 * @param img The image on which to draw the 3D object.
 * @param obj The 3D object to draw, represented by its properties.
 * @param cam_info The camera information used for projection.
 * @param color The color for drawing the object.
 * @param tf The transformation information .
 * @param rectified Whether the image is rectified or not.
 * @param line_width The width of the lines used to draw the object.
 */
void draw_object3d(cv::Mat &img,
                   const objects_msgs::msg::Object &obj,
                   const sensor_msgs::msg::CameraInfo &cam_info,
                   const cv::Vec3b &color,
                   const geometry_msgs::msg::TransformStamped *tf = nullptr,
                   bool rectified = false,
                   int line_width = 1);


/**
 * @brief Converts a `cv::Vec3b` color to `std_msgs::msg::ColorRGBA`.
 *
 * @param arr The input color in `cv::Vec3b` format.
 * @return The color in `std_msgs::msg::ColorRGBA` format.
 */
std_msgs::msg::ColorRGBA to_ColorRGBA(const cv::Vec3b& arr);


/**
 * @brief Creates visualization markers for a given object.
 * This function generates a set of visualization markers for an object, including a bounding box, edges, and an optional label.
 *
 * @param obj The object to be visualized.
 * @param header The header information to be used in the markers.
 * @param color The base color for the markers.
 * @param label The optional label to be displayed with the object.
 * @return A vector of visualization markers to represent the object.
 */
std::vector<visualization_msgs::msg::Marker> create_markers(
    const objects_msgs::msg::Object &obj,
    const std_msgs::msg::Header &header,
    const std_msgs::msg::ColorRGBA &color,
    const std::string &label
);

visualization_msgs::msg::Marker create_traj_marker(
    std_msgs::msg::Header header,
    objects_msgs::msg::DynamicObject obj,
    const std_msgs::msg::ColorRGBA& color
);


visualization_msgs::msg::Marker create_pred_marker(
    std_msgs::msg::Header header,
    objects_msgs::msg::DynamicObject obj,
    const std_msgs::msg::ColorRGBA& color
);

/**
 * @brief A pre-defined marker to delete all existing markers.
 *
 * This marker can be used to clear all previously created markers.
 */
extern const visualization_msgs::msg::Marker DELETE_ALL_MARKERS;
