## Requirements

- ROS2 Galactic or later
- OpenCV
- Eigen3

## Usage

### Install

```shell
source /opt/ros/galactic/setup.bash 
# source /opt/ros/humble/setup.bash

cd ~/ros2_ws/
git clone https://github.com/VladislavRomanichenko/objects_visualization_ros2.git

```

### RUN

```shell
cd ~/ros2_ws
source /opt/ros/galactic/setup.bash 
#source /opt/ros/humble/setup.bash
colcon build
source ./install/setup.bash

# launch with container
ros2 launch objects_vis visualization.launch.py 

```