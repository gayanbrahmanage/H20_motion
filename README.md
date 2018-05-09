# H20_motion
This package provides all the necessary drivers and programs for H20 robot. Initail programs provided by the Dr.Robot Inc have been improved to make the robot more stable in motion. The control program is based on tuned PID controller developed by Robotics and Sensor Group at University of Calgary, AB, Canada.

## How to install
Navigate to the directory you need to install using cd or orscd command.

`git clone` to present working directory.

### Install the dependency packages
The H20 driver needs dependency package called `erratic_robot`
To install that, go to H20_motion directory `cd H20_motion`

`git clone https://github.com/arebgun/erratic_robot.git `

If you havent set your package path in `~/.bashrc` ,the package is not in your package path, so set it using following or you can add line to `~/.bashrc` file `export export ROS_PACKAGE_PATH= "your pakcage path".` You can find the package path by using following ros command `echo $ROS_PACKAGE_PATH`.

export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:`pwd`

Then build the `erratic_robot` package by running `rosmake`   from the `erratic_robot` directory.

Then, switch to the directory `~/catkin_ws/H20_motion/DrRobotMotionSensorDriver`

Run `rosmake`

Then, switch to the directory `~/catkin_ws/H20_motion/drrobot_jaguar4x4_player`

Run `rosmake`
