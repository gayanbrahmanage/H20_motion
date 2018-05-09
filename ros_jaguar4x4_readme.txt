
There are 2 folders:DrRobotMotionSensorDriver and drrobot_jaguar4x4_player.

You could copy all 2 folders to your ROS working folder.
Use "make clean" in each folder to clean all the cache/build files.
Then use "rosmake" to build again.

You need make sure you already installed all the depend packages. You could find them in manifest file in drrobot_jaguar4x4_player folder.


The demo program will public all the sensor information and received command from joystick to control the robot.
After run roscore
you could use command " roslaunch drrobot_jaguar4x4_player drrobot_play1.launch" to lauch all the program.
It will auto load the parameter file "drrobotplayer_jaguar4x4.yaml" to ros parameter server.
If you modified IP, you could edit this file.

