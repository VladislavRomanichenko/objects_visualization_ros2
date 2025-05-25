from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition, UnlessCondition
from launch_ros.actions import Node, ComposableNodeContainer
from launch_ros.descriptions import ComposableNode


def generate_launch_description():
    run_as_components_arg = DeclareLaunchArgument(
        'run_as_components',
        default_value='false',
        description='Set to "true" to run nodes as components in a container, "false" to run as standalone nodes'
    )

    run_as_components = LaunchConfiguration('run_as_components')

    draw_objects_node = Node(
        package='objects_vis',
        executable='draw_objects',  
        name='draw_objects_node',
        output='screen',
        condition=UnlessCondition(run_as_components) 
    )

    draw_objects3d_node = Node(
        package='objects_vis',
        executable='draw_objects3d',  
        name='draw_objects3d_node',
        output='screen',
        condition=UnlessCondition(run_as_components)
    )

    objects2markers_node = Node(
        package='objects_vis',
        executable='objects2markers', 
        name='objects2markers_node',
        output='screen',
        condition=UnlessCondition(run_as_components),
        parameters=[{
            'color': 'label',
            'label_fmt': '{score} {id} {label}'
        }],
        remappings=[
            ('objects3d', 'centerpoint/objects3d')            
        ]
    )

    dynamic_objects2markers_node = Node(
        package='objects_vis',
        executable='dynamic_objects2markers',  
        name='dynamic_objects2markers_node',
        output='screen',
        condition=UnlessCondition(run_as_components),
        parameters=[{
            'color': 'label',
            'classes': ['car', 'person', 'cyclist'],
            'label_fmt': '{score} {id} {cls}'
        }],
        remappings=[
            ('dynamic_objects3d', '/tracking/tracking_objects')            
        ]
    )

    container = ComposableNodeContainer(
        name='objects_vis_container',
        namespace='',
        package='rclcpp_components',
        executable='component_container',
        composable_node_descriptions=[
            ComposableNode(
                package='objects_vis',
                plugin='objects_vis::DrawObjects',
                name='draw_objects_node'
            ),
            ComposableNode(
                package='objects_vis',
                plugin='objects_vis::DrawObjects3D',
                name='draw_objects3d_node'
            ),
            ComposableNode(
                package='objects_vis',
                plugin='objects_vis::Objects2Markers',
                name='objects2markers_node',
                parameters=[{
                    'color': 'label',
                    'label_fmt': '{score} {id} {label}'
                }],
                remappings=[
                    ('objects3d', 'centerpoint/objects3d')            
                ]
                
            ),
            ComposableNode(
                package='objects_vis',
                plugin='objects_vis::DynamicObjects2Markers',
                name='dynamic_objects2markers_node'
            ),
        ],
        output='screen',
        condition=IfCondition(run_as_components)
    )

    return LaunchDescription([
        run_as_components_arg,
        draw_objects_node,
        draw_objects3d_node,
        objects2markers_node,
        dynamic_objects2markers_node,
        container
    ])


if __name__ == '__main__':
    generate_launch_description()