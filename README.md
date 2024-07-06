## Requirements

- ROS2 Galactic or later
- OpenCV
- Eigen3

![image](https://github.com/VladislavRomanichenko/objects_visualization_ros2/assets/131472248/04802009-a285-401b-99be-a7ce923edaca)


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
