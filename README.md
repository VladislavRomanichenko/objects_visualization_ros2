## Requirements

- ROS2 Galactic or later
- OpenCV
- Eigen3

![photo_2024-06-28_16-52-10](https://github.com/VladislavRomanichenko/objects_visualization_ros2/assets/131472248/86a8f5c7-517e-40a5-827d-4bfbbd5870ef)



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
