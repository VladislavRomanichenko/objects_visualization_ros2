#include "../include/utils.hpp"
//#include "./utils.hpp"

Rect_::Rect_(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

cv::Point Rect_::tl()  { 
    return cv::Point(cvRound(x), cvRound(y)); 
}

cv::Point Rect_::br()  { 
    return cv::Point(cvRound(x + width), cvRound(y + height)); 
}


Eigen::Matrix4d Rt_from_tq(const geometry_msgs::msg::Point &t, const geometry_msgs::msg::Quaternion &q) {
    Eigen::Matrix4d Rt = Eigen::Matrix4d::Zero();
    Eigen::Quaterniond quat(q.w, q.x, q.y, q.z);
    Eigen::Matrix3d R = quat.toRotationMatrix();
    Rt.block<3, 3>(0, 0) = R;
    Rt.block<3, 1>(0, 3) << t.x, t.y, t.z;
    Rt(3, 3) = 1.0;
    return Rt;
}


Matrix4 Rt_from_Pose(const geometry_msgs::msg::Pose &pose) {
    return Rt_from_tq(pose.position, pose.orientation);
}


Eigen::Matrix4d Rt_from_Transform(const geometry_msgs::msg::TransformStamped &tf_stamped) {
    const auto& tf = tf_stamped.transform;
    geometry_msgs::msg::Point t;
    t.x = tf.translation.x;
    t.y = tf.translation.y;
    t.z = tf.translation.z;

    geometry_msgs::msg::Quaternion q;
    q.x = tf.rotation.x;
    q.y = tf.rotation.y;
    q.z = tf.rotation.z;
    q.w = tf.rotation.w;

    return Rt_from_tq(t, q);
}


geometry_msgs::msg::Pose Pose_from_Rt(const Matrix4 &Rt) {
    geometry_msgs::msg::Pose pose;
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


void transform_object(objects_msgs::msg::Object object, const geometry_msgs::msg::TransformStamped &tf) {
    Matrix4 Rt_tf = Rt_from_Transform(tf);
    Matrix4 Rt_pose = Rt_from_Pose(object.pose);
    
    object.pose = Pose_from_Rt(Rt_tf * Rt_pose);
}


void set_object_yaw(objects_msgs::msg::Object object, double yaw, bool camera_frame) {
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


double get_object_yaw(objects_msgs::msg::Object object, bool camera_frame) {
    
    Quaterniond quat(object.pose.orientation.w, 
                    object.pose.orientation.x, 
                    object.pose.orientation.y, 
                    object.pose.orientation.z);

    if (camera_frame) {
        Eigen::Matrix3d R = quat.toRotationMatrix();
        return std::atan2(-R(0, 0), -R(0, 1));
    } else {
        return std::atan2(object.pose.orientation.z, object.pose.orientation.w);
    }
}


std::vector<Eigen::Vector3d> object_points(objects_msgs::msg::Object object, const Matrix4& Rt) {
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
    Eigen::Matrix<double, 8, 4> transformed_pts = ((Rt * Rt_pose)* pts.transpose()).transpose();
    std::vector<Eigen::Vector3d> res;
    for (int i = 0; i < 8; ++i) {
        res.push_back(transformed_pts.row(i).head<3>());
    }
    return res;
}


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


CameraInfoMatrices cam_info_to_matrices(const sensor_msgs::msg::CameraInfo& cam_info) {
    CameraInfoMatrices matrices;
    
    matrices.K = Eigen::Map<const Eigen::Matrix<double, 3, 3>>(cam_info.k.data());
    matrices.D = Eigen::Map<const Eigen::VectorXd>(cam_info.d.data(), cam_info.d.size());
    matrices.R = Eigen::Map<const Eigen::Matrix<double, 3, 3>>(cam_info.r.data());
    matrices.P = Eigen::Map<const Eigen::Matrix<double, 3, 4>>(cam_info.p.data());

    return matrices;
}


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


cv::Vec3b object_color(int32_t label, int32_t id, std::string color){
    if(color == "id"){
        return random_color(id);
    }
    else if(color == "label"){
        return random_color(label);
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


std::string object_label(float score,
                        int32_t label_object,
                        int32_t id,
                        std::string label_fmt, 
                        std::vector<std::string> classes) {
    if (label_fmt.empty()) {
        return "";
    }

    std::unordered_map<std::string, std::string> obj_dict;

    std::stringstream label_ss;
    auto label = label_fmt;

    if (label.find("{id}") != std::string::npos) {
        label_ss << id << " ";
    } 
    if (label.find("{label}") != std::string::npos) {
        label_ss << classes[label_object] << " ";
    }
    if (label.find("{score}") != std::string::npos) {
        
        label_ss << std::fixed << std::setprecision(2) << score << " ";
    }   

    return label_ss.str();
}


Rect_ object_rect(objects_msgs::msg::Object2D &object){
    return Rect_(object.x, object.y, object.width, object.height);
}


void drawRect(cv::Mat &image, 
            cv::Point p0, 
            cv::Point p1, 
            cv::Vec3b color, 
            std::string label, 
            double font_scale){
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


void drawObject(cv::Mat &image, 
                objects_msgs::msg::Object2D object, 
                std::string color, 
                std::string label_fmt, 
                std::vector<std::string> classes, 
                double font_scale){
    cv::Vec3b result_color = object_color(object.label, object.id, color);
    std::string result_label = object_label(object.score, object.label, object.id, label_fmt, classes);
    Rect_ rect = object_rect(object);
    drawRect(image, rect.tl(), rect.br(), result_color, result_label, font_scale);
}


void draw_object3d(cv::Mat &img,
                   const objects_msgs::msg::Object &obj,
                   const sensor_msgs::msg::CameraInfo &cam_info,
                   const cv::Vec3b &color,
                   const geometry_msgs::msg::TransformStamped *tf,
                   bool rectified,
                   int line_width) {
    Eigen::Matrix4d Rt = Eigen::Matrix4d::Identity();
    if (tf) {
        Rt = Rt_from_Transform(*tf);
    }
    std::vector<Eigen::Vector3d> pts = object_points(obj, Rt);

    for (const auto &pt : pts) {
        if (pt.z() <= 0) {
            return;
        }
    }

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

        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j ++){
                K(i, j) = r.K(j,i);
            }
        }
        D = r.D;

    cv::Rodrigues(eigenToCvMat(r.R), rvec);
        tvec = cv::Mat::zeros(3, 1, CV_64F);
    }

    K_cv = eigenToCvMat(K);
    D_cv = cv::Mat(D.size(), 1, CV_64F, D.data());

    cv::Mat pts_mat = eigenVectorsToCvMat(pts);

    std::vector<cv::Point2d> ipts;

    cv::projectPoints(pts_mat, rvec, tvec, K_cv, D_cv, ipts);

    for (size_t i = 0; i < ipts.size(); ++i) {
        ipts[i] = ipts[i] * 1.0; 
    }

    for (const auto &edge : EDGES_INDICES) {
        cv::Point p1(static_cast<int>(ipts[edge.first].x), static_cast<int>(ipts[edge.first].y));
        cv::Point p2(static_cast<int>(ipts[edge.second].x), static_cast<int>(ipts[edge.second].y));
        cv::line(img, p1, p2, color, line_width, cv::LINE_AA);
    } 
}


std_msgs::msg::ColorRGBA to_ColorRGBA(const cv::Vec3b& arr) {
    std_msgs::msg::ColorRGBA color;
    color.r = arr[2] / 255.0;
    color.g = arr[1] / 255.0;
    color.b = arr[0] / 255.0;
    color.a = 1.0;
    return color;
}
std::vector<visualization_msgs::msg::Marker> create_markers(const objects_msgs::msg::Object &obj, 
                                                            const std_msgs::msg::Header &header, 
                                                            const std_msgs::msg::ColorRGBA &color, 
                                                            const std::string &label) {
  std::vector<visualization_msgs::msg::Marker> markers;

  geometry_msgs::msg::Point p = obj.pose.position;
  if (p.x == 0 && p.y == 0 && p.z == 0) {
    return markers;
  }

  std_msgs::msg::ColorRGBA colora = color;
  colora.a = 0.9;

  visualization_msgs::msg::Marker m;
  m.header = header;
  m.ns = "bbox";
  m.action = visualization_msgs::msg::Marker::ADD;
  m.type = visualization_msgs::msg::Marker::CUBE;
  m.color = colora;
  m.color.a = 0.5;
  m.scale = obj.size;
  m.pose = obj.pose;
  m.id = obj.id;
  markers.push_back(m);

  m = visualization_msgs::msg::Marker();
  m.header = header;
  m.id = obj.id;
  m.color = colora;
  m.ns = "edges";
  m.type = visualization_msgs::msg::Marker::LINE_LIST;
  m.scale.x = 0.05;
  m.pose.orientation.w = 1.0;
  auto pts = object_points(obj);
  for (const auto &edge : EDGES_INDICES) {
    geometry_msgs::msg::Point point;
    point.x = pts[edge.first](0);
    point.y = pts[edge.first](1);
    point.z = pts[edge.first](2);
    m.points.push_back(point);
    
    point.x = pts[edge.second](0);
    point.y = pts[edge.second](1);
    point.z = pts[edge.second](2);
    m.points.push_back(point);
  }
  markers.push_back(m);

  if (!label.empty()) {
    m = visualization_msgs::msg::Marker();
    m.header = header;
    m.ns = "label";
    m.id = obj.id;
    m.action = visualization_msgs::msg::Marker::ADD;
    m.type = visualization_msgs::msg::Marker::TEXT_VIEW_FACING;
    m.text = label;
    m.scale.z = 0.5;
    m.color = color;
    m.pose.position = obj.pose.position;
    m.pose.position.y -= obj.size.y / 2 + 0.2;
    markers.push_back(m);
  }

  return markers;
}


const visualization_msgs::msg::Marker DELETE_ALL_MARKERS = []() {
    visualization_msgs::msg::Marker marker;
    marker.action = visualization_msgs::msg::Marker::DELETEALL;
    return marker;
}();
