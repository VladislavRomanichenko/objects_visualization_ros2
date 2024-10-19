from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    return LaunchDescription([
        ComposableNodeContainer(
            name='visualization_container_cpp',
            namespace='visualization_cpp',
            package='rclcpp_components',
            executable='component_container_mt',
            composable_node_descriptions=[
                
                ComposableNode(
                    package='objects_vis',
                    plugin='draw_objects2d_cpp::ImageViewerNode',
                    name='draw_objects',
                    #parameters=[{'param_name': 'param_value'}],
                ),

                ComposableNode(
                    package='objects_vis',
                    plugin='draw_objects3d_cpp::DrawObjects3DNode',
                    name='draw_objects3d',
                    #parameters=[{'param_name': 'param_value'}],
                ),
                
                ComposableNode(
                    package='objects_vis',
                    plugin='objects2markers::Objects2Markers',
                    name='objects2markers',
                    #parameters=[{'param_name': 'param_value'}],
                ),

                ComposableNode(
                    package='objects_vis',
                    plugin='draw_centerpoint_cpp::CenterpointVisualization',
                    name='draw_centerpoint',
                    #parameters=[{'param_name': 'param_value'}],
                ),
            
            ],
            output='screen',
        ),
    ])
