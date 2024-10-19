#include <../include/draw_centerpoint.hpp>
namespace draw_centerpoint_cpp{
    std::vector<std::string> classMapping = {"CAR", "PED", "CYC"};


    visualization_msgs::msg::Marker create_pred_marker(std_msgs::msg::Header header, objects_msgs::msg::DynamicObject obj, float color[4])
    {
        visualization_msgs::msg::Marker marker;
        marker.header = header;
        marker.ns = "predictor/predictions";
        marker.id = obj.object.id;
        marker.type = visualization_msgs::msg::Marker::POINTS;
        marker.pose.orientation.w = 1.0;

        marker.scale.x = 0.2;
        marker.scale.y = 0.2;

        if (obj.prediction.size() > 0)
        {
            for (int i = 0; i < int(obj.prediction.size()); i++)
            {
                geometry_msgs::msg::Point p;
                p.x = obj.prediction[i].pose.position.x;
                p.y = obj.prediction[i].pose.position.y;
                p.z = obj.prediction[i].pose.position.z;
                marker.points.push_back(p);
            }
            marker.action = visualization_msgs::msg::Marker::ADD;
            marker.color.r = color[0];
            marker.color.g = color[1];
            marker.color.b = color[2];
            marker.color.a = color[3];
        }
        return marker;
    }


    visualization_msgs::msg::Marker create_bbox_marker(std_msgs::msg::Header header, objects_msgs::msg::DynamicObject obj, float color[4])
    {
        visualization_msgs::msg::Marker marker;
        marker.header = header;
        marker.ns = "predictor/objects";
        marker.id = obj.object.id;
        marker.type = visualization_msgs::msg::Marker::LINE_LIST;
        marker.action = visualization_msgs::msg::Marker::ADD;

        marker.scale.x = 0.1;
        marker.scale.y = 0.1;
        marker.scale.z = 0.1;

        marker.color.r = color[0];
        marker.color.g = color[1];
        marker.color.b = color[2];
        marker.color.a = color[3];

        if (obj.object.score < 0)
        {
            marker.color.r = 90;
            marker.color.g = 90;
            marker.color.b = 90;
            marker.color.a = 90;
        }

        marker.pose.orientation.w = 1.0;

        tf2::Quaternion q(
            obj.object.pose.orientation.x,
            obj.object.pose.orientation.y,
            obj.object.pose.orientation.z,
            obj.object.pose.orientation.w);

        tf2::Matrix3x3 m(q);
        double roll, pitch, yaw;
        m.getRPY(roll, pitch, yaw);

        float xdir[3] = {cos(float(yaw + M_PI)), sin(float(yaw + M_PI)), 0};
        float ydir[3] = {-xdir[1], xdir[0], 0};
        float center[3] = {float(obj.object.pose.position.x), float(obj.object.pose.position.y), float(obj.object.pose.position.z)};

        float vs[8][3] = {0};

        float l2 = obj.object.size.x / 2.0;
        float w2 = obj.object.size.y / 2.0;
        float h[3] = {0.0, 0.0, float(obj.object.size.z / 2.0)};

        for (int i = 0; i < 3; i++)
        {
            vs[0][i] = center[i] + xdir[i] * -l2 + ydir[i] * -w2 - h[i]; // # A bot
            vs[1][i] = center[i] + xdir[i] * -l2 + ydir[i] * w2 - h[i];  // # B bot
            vs[2][i] = center[i] + xdir[i] * l2 + ydir[i] * w2 - h[i];   // # C bot
            vs[3][i] = center[i] + xdir[i] * l2 + ydir[i] * -w2 - h[i];  // # D bot
        }

        for (int i = 0; i < 3; i++)
        {
            vs[4][i] = vs[0][i] + 2 * h[i]; // # E top
            vs[5][i] = vs[1][i] + 2 * h[i]; // # F top
            vs[6][i] = vs[2][i] + 2 * h[i]; // # G top
            vs[7][i] = vs[3][i] + 2 * h[i]; // # H top
        }
        // # filling 12 edges
        // # A -> B
        geometry_msgs::msg::Point p;
        p.x = vs[0][0];
        p.y = vs[0][1];
        p.z = vs[0][2];
        marker.points.push_back(p);
        p.x = vs[1][0];
        p.y = vs[1][1];
        p.z = vs[1][2];
        marker.points.push_back(p);

        // # B -> C
        marker.points.push_back(p);
        p.x = vs[2][0];
        p.y = vs[2][1];
        p.z = vs[2][2];
        marker.points.push_back(p);

        // # C -> D
        marker.points.push_back(p);
        p.x = vs[3][0];
        p.y = vs[3][1];
        p.z = vs[3][2];
        marker.points.push_back(p);

        // # D -> A
        marker.points.push_back(p);
        p.x = vs[0][0];
        p.y = vs[0][1];
        p.z = vs[0][2];
        marker.points.push_back(p);

        // # E -> F
        p.x = vs[4][0];
        p.y = vs[4][1];
        p.z = vs[4][2];
        marker.points.push_back(p);
        p.x = vs[5][0];
        p.y = vs[5][1];
        p.z = vs[5][2];
        marker.points.push_back(p);

        // # F -> G
        marker.points.push_back(p);
        p.x = vs[6][0];
        p.y = vs[6][1];
        p.z = vs[6][2];
        marker.points.push_back(p);

        // # G -> H
        marker.points.push_back(p);
        p.x = vs[7][0];
        p.y = vs[7][1];
        p.z = vs[7][2];
        marker.points.push_back(p);

        // # H -> E
        marker.points.push_back(p);
        p.x = vs[4][0];
        p.y = vs[4][1];
        p.z = vs[4][2];
        marker.points.push_back(p);

        // # A -> E
        p.x = vs[0][0];
        p.y = vs[0][1];
        p.z = vs[0][2];
        marker.points.push_back(p);
        p.x = vs[4][0];
        p.y = vs[4][1];
        p.z = vs[4][2];
        marker.points.push_back(p);

        // # B -> F
        p.x = vs[1][0];
        p.y = vs[1][1];
        p.z = vs[1][2];
        marker.points.push_back(p);
        p.x = vs[5][0];
        p.y = vs[5][1];
        p.z = vs[5][2];
        marker.points.push_back(p);

        // # C -> G
        p.x = vs[2][0];
        p.y = vs[2][1];
        p.z = vs[2][2];
        marker.points.push_back(p);
        p.x = vs[6][0];
        p.y = vs[6][1];
        p.z = vs[6][2];
        marker.points.push_back(p);

        // # D -> H
        p.x = vs[3][0];
        p.y = vs[3][1];
        p.z = vs[3][2];
        marker.points.push_back(p);
        p.x = vs[7][0];
        p.y = vs[7][1];
        p.z = vs[7][2];
        marker.points.push_back(p);

        // # direction as part of bbox
        float ar0[3], ar1[3], ar2[3];

        for (int i = 0; i < 3; i++)
        {
            ar0[i] = center[i] + ydir[i] * w2;
        }

        geometry_msgs::msg::Point p0, p1, p2;

        p0.x = ar0[0];
        p0.y = ar0[1];
        p0.z = ar0[2];

        for (int i = 0; i < 3; i++)
        {
            ar1[i] = center[i] - ydir[i] * w2;
        }

        p1.x = ar1[0];
        p1.y = ar1[1];
        p1.z = ar1[2];

        for (int i = 0; i < 3; i++)
        {
            ar2[i] = center[i] - xdir[i] * l2;
        }

        p2.x = ar2[0];
        p2.y = ar2[1];
        p2.z = ar2[2];

        marker.points.push_back(p0);
        marker.points.push_back(p1);
        marker.points.push_back(p1);
        marker.points.push_back(p2);
        marker.points.push_back(p2);
        marker.points.push_back(p0);
        return marker;
    }


    visualization_msgs::msg::Marker create_text_marker(std_msgs::msg::Header header, objects_msgs::msg::DynamicObject obj, float color[4])
    {
        visualization_msgs::msg::Marker marker;
        marker.header = header;
        marker.ns = "predictor/ids";
        marker.id = obj.object.id;
        marker.type = visualization_msgs::msg::Marker::TEXT_VIEW_FACING;
        marker.text = classMapping[obj.object.label] + ": " + std::to_string(obj.object.id);
        marker.action = visualization_msgs::msg::Marker::ADD;
        marker.scale.z = 0.5;

        marker.color.r = color[0];
        marker.color.g = color[1];
        marker.color.b = color[2];
        marker.color.a = color[3];

        marker.pose.orientation.w = 1.0;
        marker.pose.position.x = obj.object.pose.position.x;
        marker.pose.position.y = obj.object.pose.position.y;
        marker.pose.position.z = obj.object.pose.position.z + obj.object.size.z / 2 + 0.15;
        return marker;
    }


    visualization_msgs::msg::Marker create_velo_marker(std_msgs::msg::Header header, objects_msgs::msg::DynamicObject obj, float color[4])
    {
        visualization_msgs::msg::Marker marker;
        marker.header = header;
        marker.ns = "predictor/velocities";

        geometry_msgs::msg::Point start_p;
        start_p.x = obj.object.pose.position.x;
        start_p.y = obj.object.pose.position.y;
        start_p.z = obj.object.pose.position.z;

        float v[2] = {float(obj.velocity.linear.x), float(obj.velocity.linear.y)};

        geometry_msgs::msg::Point end_p;
        end_p.x = obj.object.pose.position.x + v[0] * 3;
        end_p.y = obj.object.pose.position.y + v[1] * 3;
        end_p.z = obj.object.pose.position.z;

        marker.points.push_back(start_p);
        marker.points.push_back(end_p);
        marker.scale.x = 0.08;
        marker.scale.y = 0.16;
        marker.scale.z = 0.08;
        marker.id = obj.object.id;
        marker.type = visualization_msgs::msg::Marker::ARROW;
        marker.action = visualization_msgs::msg::Marker::ADD;

        marker.color.r = color[0];
        marker.color.g = color[1];
        marker.color.b = color[2];
        marker.color.a = color[3];

        marker.pose.orientation.w = 1.0;
        return marker;
    }


    visualization_msgs::msg::Marker create_traj_marker(std_msgs::msg::Header header, objects_msgs::msg::DynamicObject obj, float color[4])
    {
        visualization_msgs::msg::Marker marker;
        marker.header = header;
        marker.ns = "predictor/trajectories";
        marker.id = obj.object.id;
        marker.type = visualization_msgs::msg::Marker::LINE_STRIP;
        marker.pose.orientation.w = 1.0;
        marker.scale.x = 0.2;
        if (obj.trajectory.size() > 1)
        {
            for (int i = 0; i < int(obj.trajectory.size()); i++)
                marker.points.push_back(obj.trajectory[i].point);
            marker.action = visualization_msgs::msg::Marker::ADD;

            marker.color.r = color[0];
            marker.color.g = color[1];
            marker.color.b = color[2];
            marker.color.a = color[3];
        }
        return marker;
    }


    void CenterpointVisualization::initializeParameter()
    {
        //Declare parameter for function
        this->declare_parameter<std::string>("ns", "");
        this->declare_parameter<std::string>("fixed_frame", "local_map");
        //this->declare_parameter<std::string>("objects", "/lidar_objects");

        this->visualization_on = this->declare_parameter<bool>("publish_cp_markers", true);

        ns = this->get_parameter("ns").as_string();
        fixed_frame = this->get_parameter("fixed_frame").as_string();
        //objects = this->get_parameter("objects").as_string();
    }


    void CenterpointVisualization::CenterpointCallback(const objects_msgs::msg::DynamicObjectArray::ConstSharedPtr& objects_msg) 
    {
        if(marker_pub_->get_subscription_count() == 0){
            return;
        }

        else{
            visualization_msgs::msg::MarkerArray markers;
            visualization_msgs::msg::Marker delete_all, pred_marker, bbox_marker, text_marker, traj_marker;
            
            delete_all.action = visualization_msgs::msg::Marker::DELETEALL;
            markers.markers.push_back(delete_all);

            objects_msgs::msg::DynamicObjectArray objects = *objects_msg;

            if (objects.objects.size() > 0 && this->visualization_on){
                for (int i = 0; i < int(objects.objects.size()); i++){

                    pred_marker = create_pred_marker(objects.header, objects.objects[i], COLOR_1);
                    bbox_marker = create_bbox_marker(objects.header, objects.objects[i], COLOR_2);
                    text_marker = create_text_marker(objects.header, objects.objects[i], COLOR_2);
                    traj_marker = create_traj_marker(objects.header, objects.objects[i], COLOR_2);

                    markers.markers.push_back(bbox_marker);
                    markers.markers.push_back(text_marker);

                    if (pred_marker.points.size() > 0){
                        markers.markers.push_back(pred_marker);
                    }

                    if (traj_marker.points.size() > 0){
                        markers.markers.push_back(traj_marker);
                    }
                }
            marker_pub_->publish(markers);
            }
        }
    }


    CenterpointVisualization::CenterpointVisualization(const rclcpp::NodeOptions &options) : Node("visualization_centerpoint_node", options)
    {
        RCLCPP_INFO(this->get_logger(), "Initializing ...");

        this->initializeParameter();  

        obj_sub_ = this->create_subscription<objects_msgs::msg::DynamicObjectArray>(
            "/lidar_objects", rclcpp::QoS(10),
            [this](const objects_msgs::msg::DynamicObjectArray::ConstSharedPtr msg) {
                this->CenterpointCallback(msg);
            });

        marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("marker_objects_centerpoint", 10);
        
        RCLCPP_WARN(this->get_logger(), "is visualization on: %d", this->visualization_on);
        RCLCPP_INFO(this->get_logger(), "Visualisator is ok ...");
    }
}//namespace draw_centerpoint_cpp


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions node_options;
    rclcpp::spin(std::make_shared<draw_centerpoint_cpp::CenterpointVisualization>(node_options));
    rclcpp::shutdown();
    return 0;
}

#include <rclcpp_components/register_node_macro.hpp>
/*
   Register the component with class_loader.
   This acts as a sort of entry point, allowing the component to be discoverable
   when its library is being loaded into a running process.
*/
RCLCPP_COMPONENTS_REGISTER_NODE(draw_centerpoint_cpp::CenterpointVisualization)