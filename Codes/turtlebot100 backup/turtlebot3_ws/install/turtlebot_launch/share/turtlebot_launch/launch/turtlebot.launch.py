from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    # 1. Intel Realsense D435 Node
    d435_node = Node(
        package='d435_node',
        executable='d435_node',
        name='d435_node',
        output='screen',
        parameters=[{
        }]
    )

    # 2. Dispenser Node
    dispenser_node = Node(
        package='dispenser_node',
        executable='dispenser_node',
        name='dispenser_node',
        output='screen'
    )

    return LaunchDescription([
        d435_node,
        dispenser_node
    ])
