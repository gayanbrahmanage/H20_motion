/*!
 *  drrobot_jaguar4x4_player
 *  Copyright (c) 2011, Dr Robot Inc
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <ORGANIZATION> nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*!

@mainpage
  drrobot_jaguar4x4_player is a driver for motion control system on I90/Sentinel3/Hawk/H20/X80SV/Jaguar series mobile robot, available from
<a href="http://www.drrobot.com">Dr Robot </a>.
<hr>

@section usage Usage
@par     After start roscore, you need load robot configuration file to parameter server first.
          For example, I90 robot, you need load drrobotplayer_I90.yaml use command "rosparam load drrobotplayer_I90.yaml"
@verbatim
$ drrobot_jaguar4x4_player
@endverbatim

<hr>
@section topic ROS topics

Subscribes to (name/type):
- @b "cmd_vel"/Twist : velocity commands to differentially drive the robot.
- @b will develop other command subscribles in future, such as servo control.

Publishes to (name / type):
-@b drrobot_motor: will publish MotionInfoArray Message. Please referee the message file.
-@b drrobot_powerinfo: will publish PowerInfo Message. Please referee the message file.
-@b drrobot_ir: will publish RangeArray Message for IR sensor, and transform AD value from DrRobotMotionSensorDriver to distance value in unit meter. Please referee the message file.
-@b drrobot_sonar: will publish RangeArray Message for ultrasonic sensor, and transform value from DrRobotMotionSensorDriver to distance value in unit meter. Please referee the message file.
-@b drrobot_standardsensor: will publish StandardardSensor Message. Please referee the message file.
-@b drrobot_customsensor: will publish CustomSensor Message. Please referee the message file. Not available for standard I90/Sentinel3/Hawk/H20/X80SV robot

<hr>

@section parameters ROS parameters, please read yaml file

- @b RobotCommMethod (string) : Robot communication method, normally is "Network".
- @b RobotID (string) : specify the robot ID
- @b RobotBaseIP (string) : robot main WiFi module IP address in dot format, default is "192.168.0.201".
- @b RobotPortNum (string) : socket port number first serial port, and as default the value increased by one will be second port number.
- @b RobotSerialPort (int) : specify the serial port name if you choose serial communication in RobotCommMethod, default /dev/ttyS0"
- @b RobotType (string) : specify the robot type, now should in list: I90, Sentinel3, Hawk_H20, Jaguar, X80SV
- @b MotorDir (int) : specify the motor control direction
- @b WheelRadius (double) : wheel radius
- @b WheelDistance (double) : the distance between two driving wheels
- @b EncoderCircleCnt (int) : one circle encoder count
- @b MinSpeed (double) : minimum speed, unit is m/s.
- @b MaxSpeed (double) : maximum speed, unit is m/s.
- @b enable_ir (bool)  : Whether to enable sonar range sensors. Default: true.
- @b enable_sonar (bool)  : Whether to enable IR range sensors. Default: true.
 */
#include <iostream>
#include <Matrix.h>
#include <Eigen/Dense>
#include <assert.h>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

#include <sensor_msgs/JointState.h>
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>


#include <std_msgs/Float64.h>
#include <std_msgs/MultiArrayLayout.h>
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"

#include <sstream>  //added
#include <drrobot_jaguar4x4_player/variable.h>  //added
#include <drrobot_jaguar4x4_player/Rscanpose.h>  //added for save the scan plus encorder for EKF implemetation offline
#include <drrobot_jaguar4x4_player/KFodom.h>  //added
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include "sensor_msgs/LaserScan.h"

#include <drrobot_jaguar4x4_player/MotorInfo.h>
#include <drrobot_jaguar4x4_player/MotorInfoArray.h>
#include <drrobot_jaguar4x4_player/RangeArray.h>
#include <drrobot_jaguar4x4_player/Range.h>
#include <drrobot_jaguar4x4_player/PowerInfo.h>
#include <drrobot_jaguar4x4_player/StandardSensor.h>
#include <drrobot_jaguar4x4_player/CustomSensor.h>
#include "DrRobotMotionSensorDriver.hpp"




#define MOTOR_NUM       6
#define IR_NUM          10
#define US_NUM          6
#define cFULL_COUNT				32767
#define cWHOLE_RANGE			1200
#define ENCODER_SCALAR_H20		0.00155		//1revoultion of wheel = .53m/400encoder readings//theoretical 0.001399055
#define TRACK					0.425				//Distance between two wheels(cm)

using namespace Eigen;
using namespace std;
using namespace DrRobot_MotionSensorDriver;
//----------------------------------------------------------------------
	double dt;
	int encoder1, encoder2;
	
	int encoderLeft=0, encoderRight=0;
	
	int encoderDir_L, encoderDir_R;
	int encoder_difference=0;
	int temp_encorderLeft;
	int temp_encorderRight;
	int diff_encoderLeft=0;
	int diff_encoderRight=0;
	int preEncoder1=0;
	int preEncoder2=0;
	
	
	int pre_encorder_difference=0;
    int rate_encorder_difference=0;
    
	double wheel_speed_L, wheel_speed_R;
	
	int initial = 0;
	double x_1=0, y_1=0,theta_1=0, rotational_theta=0;
//----------------------------------------------------------------------
	double x_displacement=0;
	
	double x=0,y=0,theta=0,alpha=0,previous_alpha=0,alpha_dot=0,alpha_I=0,beta=0;
	
	double p=0, p_dot=0,previous_p=0;
	
	double g_coordinates_x=0,x_coordinates_error=0;
    double g_coordinates_y=0,y_coordinates_error=0;
    double t_angle=0,t_angle_old=0;
	
	double deltaD=0;
	double deltaTheta=0;
	double thetaIntergral=0;
	double velocity_angle=0;
//----------------------------------------------------------------------
	double Vx=0, Vy=0,Vz=0,Vxy=0,Vr=0,Wr=0; //word coordinate /robot coordinates frames
	double  robotVx=0; //No robotVy
	double Vcommand=0,command=0;
	
	double f_w_left=0,f_w_right=0;
	double w_left=0;
	double w_right=0;
//----------------------------------------------------------------------
	double command_v=50,s=0;
//----------------------------------------------------------------------
	int loopcount=0;
	double pi=M_PI; //3.1415927;
//----------------------------------------------------------------------

	double gvariable1=0;
	double gvariable2=0;
	double gvariable0=0;
//----------------------------------------------------------------------
    int left_PWM=16384,right_PWM=16384;
    int Wheel_1_velocity[3],Wheel_2_velocity[3];
    int W_left_wheel_error_I=0,W_right_wheel_error_I=0;
    int W_left_wheel_error_Previous=0,W_right_wheel_error_Previous=0;
    
    int w_left_wheel, w_right_wheel,w_pre_left_wheel=0,w_pre_right_wheel=0;
    int D_encorder1,D_encorder2;
    double K_e_l,K_e_r;
//----------------------------------------------------------------------
	double scanpose[645];
//----------------------------------------------------------------------
   
	
class DrRobotPlayerNode
{
public:

    ros::NodeHandle node_;

    tf::TransformBroadcaster tf_;
	tf::TransformBroadcaster odom_broadcaster;
	tf::TransformBroadcaster path_broadcaster;
    
    ros::Publisher motorInfo_pub_;
    ros::Publisher powerInfo_pub_;
    ros::Publisher ir_pub_;
    ros::Publisher sonar_pub_;
    ros::Publisher standardSensor_pub_;
    ros::Publisher customSensor_pub_;
	ros::Publisher odom_pub_;
	ros::Publisher Rscanpose_publisher;
	
    ros::Subscriber cmd_vel_sub_;
    ros::Subscriber cmd_DesiredPose_sub;
    ros::Subscriber scan_sub;
    
	ros::Publisher path_pub_;
	ros::Publisher variable_publisher;
	ros::Publisher encorder_publisher;
	ros::Publisher KFodom_publisher;
	
    ros::Subscriber new_cmd_sub_;
    std::string robot_prefix_;

	ros::Time current_time, last_time;

	double enc_count_left;   //encorder count 
	double enc_count_right;
	double x;
	double y;
	double th;	
	double vr;
	double vl;
	double vth;
	
//======================================================================

    DrRobotPlayerNode()
    {
        ros::NodeHandle private_nh("~");

        robotID_ = "drobot1";
        private_nh.getParam("RobotID",robotID_);
        ROS_INFO("I get ROBOT_ID: [%s]", robotID_.c_str());

        robotType_ = "Jaguar";
        private_nh.getParam("RobotType",robotType_);
        ROS_INFO("I get ROBOT_Type: [%s]", robotType_.c_str());

        robotCommMethod_ = "Network";
        private_nh.getParam("RobotCommMethod",robotCommMethod_);
        ROS_INFO("I get ROBOT_CommMethod: [%s]", robotCommMethod_.c_str());

        robotIP_ = "192.168.0.60";
        private_nh.getParam("RobotBaseIP",robotIP_);
        ROS_INFO("I get ROBOT_IP: [%s]", robotIP_.c_str());

        commPortNum_ = 10001;
        private_nh.getParam("RobotPortNum",commPortNum_);
        ROS_INFO("I get ROBOT_PortNum: [%d]", commPortNum_);

        robotSerialPort_ = "/dev/ttyS0";
        private_nh.getParam("RobotSerialPort",robotSerialPort_);
        ROS_INFO("I get ROBOT_SerialPort: [%s]", robotSerialPort_.c_str());

        enable_ir_ = true;
        private_nh.getParam("Enable_IR", enable_ir_);
        if (enable_ir_)
          ROS_INFO("I get Enable_IR: true");
        else
          ROS_INFO("I get Enable_IR: false");


        enable_sonar_ = true;
        private_nh.getParam("Enable_US", enable_sonar_);
        if (enable_sonar_)
          ROS_INFO("I get Enable_US: true");
        else
          ROS_INFO("I get Enable_US: false");

        motorDir_ = 1;
        private_nh.getParam("MotorDir", motorDir_);
        ROS_INFO("I get MotorDir: [%d]", motorDir_);

        wheelRadius_ = 0.0835;
        private_nh.getParam("WheelRadius", wheelRadius_);
        ROS_INFO("I get Wheel Radius: [%f]", wheelRadius_);

        wheelDis_ = 0.305;
        private_nh.getParam("WheelDistance", wheelDis_);
        ROS_INFO("I get Wheel Distance: [%f]", wheelDis_);

        minSpeed_ = 0.1;
        private_nh.getParam("MinSpeed", minSpeed_);
        ROS_INFO("I get Min Speed: [%f]", minSpeed_);

        maxSpeed_ = 1.0;
        private_nh.getParam("MaxSpeed", maxSpeed_);
        ROS_INFO("I get Max Speed: [%f]", maxSpeed_);

        encoderOneCircleCnt_ = 400;
        private_nh.getParam("EncoderCircleCnt", encoderOneCircleCnt_);
        ROS_INFO("I get Encoder One Circle Count: [%d]", encoderOneCircleCnt_);

        if (robotCommMethod_ == "Network")
        {
          robotConfig1_.commMethod = Network;
          robotConfig2_.commMethod = Network;
        }
        else
        {
          robotConfig1_.commMethod = Serial;
          robotConfig2_.commMethod = Serial;
        }

        if (robotType_ == "Jaguar")
        {
          robotConfig1_.boardType = Jaguar;
        }
        else if(robotType_ == "I90")
        {
          robotConfig1_.boardType = I90_Power;
          robotConfig2_.boardType = I90_Motion;
        }
        else if (robotType_ == "Sentinel3")
        {
          robotConfig1_.boardType = Sentinel3_Power;
          robotConfig2_.boardType = Sentinel3_Motion;
        }
        else if (robotType_ == "Hawk_H20")
        {
          robotConfig1_.boardType = Hawk_H20_Power;
          robotConfig2_.boardType = Hawk_H20_Motion;
        }
        else if(robotType_ == "X80SV")
        {
          robotConfig1_.boardType = X80SV;
        }

        robotConfig1_.portNum = commPortNum_;
        robotConfig2_.portNum = commPortNum_ + 1;

      //  strcat(robotConfig1_.robotIP,robotIP_.c_str());
	  strcpy(robotConfig1_.robotIP,robotIP_.c_str());    
      //  strcat(robotConfig2_.robotIP,robotIP_.c_str());
	  strcpy(robotConfig2_.robotIP,robotIP_.c_str());

      //  strcat(robotConfig1_.serialPortName,robotSerialPort_.c_str());
	  strcpy(robotConfig1_.serialPortName,robotSerialPort_.c_str());
      //  strcat(robotConfig2_.serialPortName,robotSerialPort_.c_str());
	  strcpy(robotConfig2_.serialPortName,robotSerialPort_.c_str());
        //create publishers for sensor data information
        motorInfo_pub_ = node_.advertise<drrobot_jaguar4x4_player::MotorInfoArray>("drrobot_motor", 10);
        powerInfo_pub_ = node_.advertise<drrobot_jaguar4x4_player::PowerInfo>("drrobot_powerinfo", 10);
        if (enable_ir_) { ir_pub_ = node_.advertise<drrobot_jaguar4x4_player::RangeArray>("drrobot_ir", 10); }
        if (enable_sonar_) { sonar_pub_ = node_.advertise<drrobot_jaguar4x4_player::RangeArray>("drrobot_sonar",10); }
        standardSensor_pub_ = node_.advertise<drrobot_jaguar4x4_player::StandardSensor>("drrobot_standardsensor", 10);
        customSensor_pub_ = node_.advertise<drrobot_jaguar4x4_player::CustomSensor>("drrobot_customsensor", 10);
		
		odom_pub_ = node_.advertise<nav_msgs::Odometry>("odom", 1000);
		Rscanpose_publisher= node_.advertise<drrobot_jaguar4x4_player::Rscanpose>("Rscanpose", 1000);//added to save scan plus encorder for EKF offline
		path_pub_ = node_.advertise<nav_msgs::Path>("path", 1000);
		variable_publisher = node_.advertise<drrobot_jaguar4x4_player::variable>("variable", 1000);//added
		encorder_publisher = node_.advertise<std_msgs::Int32MultiArray>("encorder", 1000);//added
		KFodom_publisher = node_.advertise<drrobot_jaguar4x4_player::KFodom>("KFodom", 1000);//added	

        drrobotPowerDriver_ = new DrRobotMotionSensorDriver();
        drrobotMotionDriver_ = new DrRobotMotionSensorDriver();
        if (  (robotType_ == "Jaguar") )
        {
          drrobotMotionDriver_->setDrRobotMotionDriverConfig(&robotConfig1_);
        }
        else
        {
          drrobotPowerDriver_->setDrRobotMotionDriverConfig(&robotConfig1_);
          drrobotMotionDriver_->setDrRobotMotionDriverConfig(&robotConfig2_);
        }
        cntNum_ = 0;
    
		x = 0.0;
		y = 0.0;
		th = 0.0;
   
    
    
		current_time = ros::Time::now();
		last_time = ros::Time::now();
		
		enc_count_left=0; //encorder init
		enc_count_right=0;
    
    }

    ~DrRobotPlayerNode()
    {
    }
//======================================================================
    int start()
    {

      int res = -1;
      if (  (robotType_ == "Jaguar"))
      {
        res = drrobotMotionDriver_->openNetwork(robotConfig1_.robotIP,robotConfig1_.portNum);
	if (res == 0)
	{
		ROS_INFO("open port number at: [%d]", robotConfig1_.portNum);
	}
	else
	{
		ROS_INFO("could not open network connection to [%s,%d]",  robotConfig1_.robotIP,robotConfig1_.portNum);
		//ROS_INFO("error code [%d]",  res);
	}

      }
      else
      {
        drrobotMotionDriver_->openNetwork(robotConfig2_.robotIP,robotConfig2_.portNum);
        drrobotPowerDriver_->openNetwork(robotConfig1_.robotIP,robotConfig1_.portNum);

      }
      
     cmd_vel_sub_ = node_.subscribe<geometry_msgs::Twist>("cmd_vel", 1, boost::bind(&DrRobotPlayerNode::cmdVelReceived, this, _1));
     scan_sub= node_.subscribe<sensor_msgs::LaserScan>("scan", 1, boost::bind(&DrRobotPlayerNode::processLaserScan, this, _1));
     new_cmd_sub_ = node_.subscribe<geometry_msgs::Twist>("new_cmd", 1, boost::bind(&DrRobotPlayerNode::cmdNewCommand, this, _1));
     
     
       return(0);
    }
//======================================================================
    int stop()
    {
        int status = 0;
         drrobotMotionDriver_->close();
        drrobotPowerDriver_->close();
        usleep(1000000);
        return(status);
    }
//======================================================================
	void cmdNewCommand(const geometry_msgs::Twist::ConstPtr& new_cmd)
	{
			ROS_INFO("Got new command");
			
	}

//======================================================================
 void cmdVelReceived(const geometry_msgs::Twist::ConstPtr& cmd_vel)
    {
		
	  
     g_coordinates_x= cmd_vel->linear.x;
     g_coordinates_y= cmd_vel->linear.y;
     t_angle = cmd_vel->angular.z;
     command=cmd_vel->linear.z;


    }
    
//======================================================================
void processLaserScan(const sensor_msgs::LaserScan::ConstPtr& scan){
	
	gvariable1=scan->ranges[15];
	int i=5;
	for(i=5;i<645;i++){
		scanpose[i]=scan->ranges[i-5];
	}	
}

//======================================================================
 void doUpdate()
    {
		ROS_INFO("Gayan Workspace");
		ROS_INFO("Desired: [X= %f,Y= %f,Theta= %f]",g_coordinates_x,g_coordinates_y,t_angle*180/pi);
		ROS_INFO("Current: [X= %f,Y= %f,Theta= %f]",x,y,theta*180/pi);
		ROS_INFO("Encoder: [EncoderL = %d, EncoderR = %d]", encoderLeft, encoderRight);
		ROS_INFO("Encoder: [DiffEncoderL = %d, DiffEncoderR = %d]", diff_encoderLeft, diff_encoderRight);
		ROS_INFO("Encoder: [EncoderD_L = %d, EncoderD_R = %d]", encoderDir_L, encoderDir_R);
		
		ROS_INFO("Variable: [GVARIABLE1 = %f,GVARIABLE2 = %f]",gvariable1, gvariable2 );
		ROS_INFO("WHEEL: [Wleft= %f,Wright= %f]",w_left_wheel*2*pi/375,w_right_wheel*2*pi/375);
		ROS_INFO("Motion: [Vx= %f,Vy= %f,Vz=%f]",Vx,Vy,Vz);
		ROS_INFO("Motion: [Vxy= %f,dt=%f]",Vxy,dt);
		ROS_INFO("Motion: [P= %f,Beta= %f,Alpha= %f]",p,beta*180/pi,alpha*180/pi);
		
		//CALCULATE MOTOR STEERING
			
		//ComputeSteering(motorSensorData_.motorSensorEncoderPos[0],motorSensorData_.motorSensorEncoderPos[1],motorSensorData_.motorSensorEncoderDir[0],motorSensorData_.motorSensorEncoderDir[1]);
//g_coordinates_x= 0.0;
//g_coordinates_y= 0.0;

		update_parameters();
		if(command==0.0)move(g_coordinates_x,g_coordinates_y,t_angle);
		else if(command==1.0)rotate();
		publish_variables();
		//publish_encorder();
		publish_KFodom();
		
      if ( (robotConfig1_.boardType == I90_Power) || (robotConfig1_.boardType == Sentinel3_Power)
          || (robotConfig1_.boardType == Hawk_H20_Power) )
      {
        if (drrobotPowerDriver_->portOpen())
        {
          drrobotPowerDriver_->readPowerSensorData(&powerSensorData_);
          drrobot_jaguar4x4_player::PowerInfo powerInfo;
          powerInfo.ref_vol = 1.5 * 4095 /(double)powerSensorData_.refVol;

          powerInfo.bat1_vol = (double)powerSensorData_.battery1Vol  * 8 / 4095 * powerInfo.ref_vol;
          powerInfo.bat2_vol = (double) powerSensorData_.battery2Vol * 8 / 4095 * powerInfo.ref_vol;

          powerInfo.bat1_temp = powerSensorData_.battery1Thermo;
          powerInfo.bat2_temp = powerSensorData_.battery2Thermo;

          powerInfo.dcin_vol = (double)powerSensorData_.dcINVol * 8 / 4095 * powerInfo.ref_vol;
          powerInfo.charge_path = powerSensorData_.powerChargePath;
          powerInfo.power_path = powerSensorData_.powerPath;
          powerInfo.power_status = powerSensorData_.powerStatus;

          powerInfo_pub_.publish(powerInfo);
        }
      }
      if (drrobotMotionDriver_->portOpen())
      {
        drrobotMotionDriver_->readMotorSensorData(&motorSensorData_);
        drrobotMotionDriver_->readRangeSensorData(&rangeSensorData_);
        drrobotMotionDriver_->readStandardSensorData(&standardSensorData_);

        drrobotMotionDriver_->readCustomSensorData(&customSensorData_);
              // Translate from driver data to ROS data
            cntNum_++;
              drrobot_jaguar4x4_player::MotorInfoArray motorInfoArray;
              motorInfoArray.motorInfos.resize(MOTOR_NUM);
              for (uint32_t i = 0 ; i < MOTOR_NUM; ++i)
              {
                  motorInfoArray.motorInfos[i].header.stamp = ros::Time::now();
                  motorInfoArray.motorInfos[i].header.frame_id = string("drrobot_motor_");
                  motorInfoArray.motorInfos[i].header.frame_id += boost::lexical_cast<std::string>(i);
                  motorInfoArray.motorInfos[i].robot_type = robotConfig1_.boardType;
                  motorInfoArray.motorInfos[i].encoder_pos = motorSensorData_.motorSensorEncoderPos[i];
                  motorInfoArray.motorInfos[i].encoder_vel = motorSensorData_.motorSensorEncoderVel[i];
                  motorInfoArray.motorInfos[i].encoder_dir = motorSensorData_.motorSensorEncoderDir[i];
                  if (robotConfig1_.boardType == Hawk_H20_Motion)
                  {
                    motorInfoArray.motorInfos[i].motor_current = (float)motorSensorData_.motorSensorCurrent[i] * 3 /4096;;
                  }
                  else if(robotConfig1_.boardType != Jaguar)
                  {
                    motorInfoArray.motorInfos[i].motor_current = (float)motorSensorData_.motorSensorCurrent[i] / 728;
                  }
                  else
                  {
                    motorInfoArray.motorInfos[i].motor_current = 0.0;
                  }
                  motorInfoArray.motorInfos[i].motor_pwm = motorSensorData_.motorSensorPWM[i];
              }

			
			
			
			
			
		/*	// Compute Velocity Motion Model - Odometry
			//compute odometry in a typical way given the velocities of the robot
			current_time = ros::Time::now();
			
			enc_count_left = motorSensorData_.motorSensorEncoderVel[0]*motorSensorData_.motorSensorEncoderDir[0];  //left 0
			enc_count_right = -motorSensorData_.motorSensorEncoderVel[1]*motorSensorData_.motorSensorEncoderDir[1]; //right 1
      
      diffEncoder1
			vr=(enc_count_right/encoderOneCircleCnt_)*3.14*wheelRadius_*2; 
			vl=(enc_count_left/encoderOneCircleCnt_)*3.14*wheelRadius_*2; 
			vth=(vr-vl)/wheelDis_;
			
			
			
			double dt = (current_time - last_time).toSec();
			double delta_x = (vl+vr)/2.0*cos(vth) * dt;
			double delta_y = (vl+vr)/2.0*sin(vth) * dt;
			double delta_th = vth * dt;
		
			x += delta_x;
			y += delta_y;
			th += delta_th;






	ROS_INFO("(X,Y,Th) = (%f,%f,%f)",x,y,th);


			//since all odometry is 6DOF we'll need a quaternion created from yaw
			geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

			//first, we'll publish the transform over tf
			geometry_msgs::TransformStamped odom_trans;
			odom_trans.header.stamp = current_time;
			odom_trans.header.frame_id = "odom";
			odom_trans.child_frame_id = "base_link";

			odom_trans.transform.translation.x = x;
			odom_trans.transform.translation.y = y;
			odom_trans.transform.translation.z = 0.0;
			odom_trans.transform.rotation = odom_quat;

			//send the transform
			odom_broadcaster.sendTransform(odom_trans);

			//next, we'll publish the odometry message over ROS
			nav_msgs::Odometry odom;
			odom.header.stamp = current_time;
			odom.header.frame_id = "odom";

			//set the position
			odom.pose.pose.position.x = x;
			odom.pose.pose.position.y = y;
			odom.pose.pose.position.z = 0.0;
			odom.pose.pose.orientation = odom_quat;

			//set the velocity
			odom.child_frame_id = "base_link";
			odom.twist.twist.linear.x = (vl+vr)/2.0*cos(vth);
			odom.twist.twist.linear.y = (vl+vr)/2.0*sin(vth);
			odom.twist.twist.angular.z = vth;
		
			//publish the message
			odom_pub_.publish(odom);

			last_time = current_time;
			//// Finished computing odometry from the velocity



		*/
              //ROS_INFO("publish motor info array");
              motorInfo_pub_.publish(motorInfoArray);


              drrobot_jaguar4x4_player::RangeArray rangerArray;
              rangerArray.ranges.resize(US_NUM);
	      if(enable_sonar_)
	      {
		      for (uint32_t i = 0 ; i < US_NUM; ++i)
		      {

		          rangerArray.ranges[i].header.stamp = ros::Time::now();
		          rangerArray.ranges[i].header.frame_id = string("drrobot_sonar_");
		          rangerArray.ranges[i].header.frame_id += boost::lexical_cast<std::string>(i);
		          rangerArray.ranges[i].range = (float)rangeSensorData_.usRangeSensor[i]/100;     //to meters

		          // around 30 degrees
		          rangerArray.ranges[i].field_of_view = 0.5236085;
		          rangerArray.ranges[i].max_range = 2.55;
		          rangerArray.ranges[i].min_range = 0;
		          rangerArray.ranges[i].radiation_type = drrobot_jaguar4x4_player::Range::ULTRASOUND;
		      }

		      sonar_pub_.publish(rangerArray);
		}


	      if(enable_ir_)
	      {
		      rangerArray.ranges.resize(IR_NUM);
		      for (uint32_t i = 0 ; i < IR_NUM; ++i)
		      {
		          rangerArray.ranges[i].header.stamp = ros::Time::now();
		          rangerArray.ranges[i].header.frame_id = string("drrobot_ir_");
		          rangerArray.ranges[i].header.frame_id += boost::lexical_cast<std::string>(i);
		          rangerArray.ranges[i].range = ad2Dis(rangeSensorData_.irRangeSensor[i]);
		          rangerArray.ranges[i].radiation_type = drrobot_jaguar4x4_player::Range::INFRARED;
		      }

		      ir_pub_.publish(rangerArray);
	     }

              drrobot_jaguar4x4_player::StandardSensor standardSensor;
              standardSensor.humanSensorData.resize(4);
              standardSensor.tiltingSensorData.resize(2);
              standardSensor.overHeatSensorData.resize(2);
              standardSensor.header.stamp = ros::Time::now();
              standardSensor.header.frame_id = string("drrobot_standardsensor");
              for (uint32_t i = 0; i < 4; i++)
                standardSensor.humanSensorData[i] = standardSensorData_.humanSensorData[i];
              for (uint32_t i = 0; i < 2; i++)
                standardSensor.tiltingSensorData[i] = standardSensorData_.tiltingSensorData[i];
              for (uint32_t i = 0; i < 2; i++)
                standardSensor.overHeatSensorData[i] = standardSensorData_.overHeatSensorData[i];

              standardSensor.thermoSensorData = standardSensorData_.thermoSensorData;

              standardSensor.boardPowerVol = (double)standardSensorData_.boardPowerVol * 9 /4095;
              standardSensor.servoPowerVol = (double)standardSensorData_.servoPowerVol * 9 /4095;

              if (robotConfig1_.boardType != Jaguar)
              {
                standardSensor.motorPowerVol = (double)standardSensorData_.motorPowerVol * 24 /4095;
              }
              else
              {
                standardSensor.motorPowerVol = (double)standardSensorData_.motorPowerVol * 34.498 /4095;
              }
              standardSensor.refVol = (double)standardSensorData_.refVol / 4095 * 6;
              standardSensor.potVol = (double)standardSensorData_.potVol / 4095 * 6;
              standardSensor_pub_.publish(standardSensor);

              drrobot_jaguar4x4_player::CustomSensor customSensor;
              customSensor.customADData.resize(8);
              customSensor.header.stamp = ros::Time::now();
              customSensor.header.frame_id = string("drrobot_customsensor");

              for (uint32_t i = 0; i < 8; i ++)
              {
                customSensor.customADData[i] = customSensorData_.customADData[i];
              }
              customSensor.customIO = (uint8_t)(customSensorData_.customIO & 0xff);
              customSensor_pub_.publish(customSensor);
      }
      ComputeSteering(motorSensorData_.motorSensorEncoderPos[0],motorSensorData_.motorSensorEncoderPos[1],motorSensorData_.motorSensorEncoderVel[0],motorSensorData_.motorSensorEncoderVel[1],motorSensorData_.motorSensorEncoderDir[0],motorSensorData_.motorSensorEncoderDir[1]);
      	
      
      	
      	//gvariable1= (motorSensorData_.motorSensorEncoderPos[0]-gvariable0)/dt;
      	//gvariable0=motorSensorData_.motorSensorEncoderPos[0];
		//gvariable2=motorSensorData_.motorSensorEncoderVel[0]*2*pi/375;
    }

//======================================================================
void sendTransform()
	{
	  broadcaster_.sendTransform(
      tf::StampedTransform(
      tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.05, 0.0, 0.75)),   //x,y,z
      ros::Time::now(), "base_link", "camera_link" ));  //parent, child
}
//======================================================================
void publish_variables(){
drrobot_jaguar4x4_player::variable var;
var.variable0=gvariable0;
var.variable1=gvariable1;
var.variable2=gvariable2;

variable_publisher.publish(var);
}
//======================================================================
void publish_Rscanpose(){
drrobot_jaguar4x4_player::Rscanpose msg;

int i=0;
for(i=0;i<645;i++){
			msg.Rscanpose[i]=scanpose[i];
		}

Rscanpose_publisher.publish(msg);
}
//======================================================================
void publish_encorder(){
std_msgs::Int32MultiArray encorderArray;
encorderArray.data.clear();
encorderArray.data.push_back(D_encorder1);
encorderArray.data.push_back(D_encorder2);
encorder_publisher.publish(encorderArray);
}

//======================================================================
void publish_KFodom(){
drrobot_jaguar4x4_player::KFodom var;
var.deltaD=deltaD;
var.deltatheta=deltaTheta;
var.Ddot=deltaD/dt;
var.thetadot=deltaTheta/dt;

KFodom_publisher.publish(var);
}

//----------------------------------------------------------------------
//				ROBOT Rotate
//----------------------------------------------------------------------
void rotate(){
	
			beta=t_angle;
			
			alpha=beta-theta;
			if(t_angle_old==t_angle)alpha_dot=(alpha-previous_alpha)/dt;
		
			previous_alpha=alpha;
			alpha_I=alpha_I+alpha*dt;
		
			t_angle_old=t_angle;
	     
 if (robotConfig1_.boardType != Jaguar)
      {
	double Kp_p=0.0, Kd_p=0.0;
	double Kp_alpha=1.9, Kd_alpha=1.0 ,Ki_alpha=0.03; //2.0-1.0-0.03
	double Kp_beta=0;
	
		 Vr=Kp_p*p+Kd_p*p_dot;;   //%v=Kp*p+Kd*pdot;
		 Wr=Kp_alpha*alpha+Kd_alpha*alpha_dot+Ki_alpha*alpha_I; //%w=K_alpha*alpha+Kd_alpha*aplha_dot;
		 
		 if(abs(alpha)>0.03){
		 w_left=(2*Vr-Wr*TRACK)/(2*wheelRadius_ ); //WL=(2*v-w*d)/(2*r);
		 w_right=(2*Vr+Wr*TRACK)/(2*wheelRadius_ ); //WR=(2*v+w*d)/(2*r);
		 }
		 
		 else{
		 w_left=0; //WL=(2*v-w*d)/(2*r);
		 w_right=0; //WR=(2*v+w*d)/(2*r); 
		 alpha_I=0;
		 }
		 

      }
      
      
else {
	  /*
         int forwardPWM = -motorDir_ * g_coordinates_x * 16384 + 16384;
         int turnPWM = -motorDir_ * t_angle * 16384 + 16384;
         if (forwardPWM > 32767) forwardPWM = 32767;
         if (forwardPWM < 0) forwardPWM = 0;
         if (turnPWM > 32767) turnPWM = 32767;
         if (turnPWM < 0) turnPWM = 0;        
         drrobotMotionDriver_->sendMotorCtrlAllCmd(PWM,NOCONTROL,NOCONTROL,NOCONTROL,forwardPWM,turnPWM, NOCONTROL);/////////////////////////////////////////////////////////////////////////////////////////////////
      */
      }	

    //drrobotMotionDriver_->sendMotorCtrlAllCmd(PWM,left_PWM, right_PWM,NOCONTROL,NOCONTROL, NOCONTROL,NOCONTROL);///// use this -Recent PID controller rotate	
	//drrobotMotionDriver_->sendMotorCtrlAllCmd(Velocity,300, -300,NOCONTROL,NOCONTROL, NOCONTROL,NOCONTROL);
}
//----------------------------------------------------------------------
//				Trajectory control
//----------------------------------------------------------------------

void move(double g_coordinates_x, double g_coordinates_y, double t_angle) //target values
{

			x_coordinates_error=g_coordinates_x-x;
			y_coordinates_error=g_coordinates_y-y;
		
			p=sqrt(x_coordinates_error*x_coordinates_error+y_coordinates_error*y_coordinates_error);
			p_dot=(p-previous_p)/dt;
			previous_p=p;
			

			beta=atan2(g_coordinates_y-y,g_coordinates_x-x);
			
			alpha=beta-theta;
			alpha_dot=(alpha-previous_alpha)/dt;
			previous_alpha=alpha;
			alpha_I=alpha_I+alpha*dt;
			
			p_dot=(p-previous_p)/dt;
			previous_p=p;
			
//gvariable0=alpha_dot;
//gvariable1=theta*180/pi;
     
 if (robotConfig1_.boardType != Jaguar)
      {
	double Kp_p=1.4, Kd_p=0.1;  //1.4-0.0
	double Kp_alpha=2.5, Kd_alpha=0.7,Ki_alpha=0.08; //2.3-0.9-0.06
	double Kp_beta=0;
	
		 Vr=Kp_p*p+Kd_p*p_dot;;   //%v=Kp*p+Kd*pdot;
		 Wr=Kp_alpha*alpha+Kd_alpha*alpha_dot+Ki_alpha*alpha_I; //%w=K_alpha*alpha+Kd_alpha*aplha_dot;
		 
		 if(p>0.15){
		 w_left=(2*Vr-Wr*TRACK)/(2*wheelRadius_ ); //WL=(2*v-w*d)/(2*r);
		 w_right=(2*Vr+Wr*TRACK)/(2*wheelRadius_ ); //WR=(2*v+w*d)/(2*r);
		 }
		 
		 else{
		 w_left=0; //WL=(2*v-w*d)/(2*r);
		 w_right=0; //WR=(2*v+w*d)/(2*r); 
		 }
		 

      }
      
      
else {
	  /*
         int forwardPWM = -motorDir_ * g_coordinates_x * 16384 + 16384;
         int turnPWM = -motorDir_ * t_angle * 16384 + 16384;
         if (forwardPWM > 32767) forwardPWM = 32767;
         if (forwardPWM < 0) forwardPWM = 0;
         if (turnPWM > 32767) turnPWM = 32767;
         if (turnPWM < 0) turnPWM = 0;        
         drrobotMotionDriver_->sendMotorCtrlAllCmd(PWM,NOCONTROL,NOCONTROL,NOCONTROL,forwardPWM,turnPWM, NOCONTROL);/////////////////////////////////////////////////////////////////////////////////////////////////
      */
      }	

    drrobotMotionDriver_->sendMotorCtrlAllCmd(PWM,left_PWM, right_PWM,NOCONTROL,NOCONTROL, NOCONTROL,NOCONTROL);/////	///// use this-Recent PID controller move
	//drrobotMotionDriver_->sendMotorCtrlAllCmd(Velocity,300, -300,NOCONTROL,NOCONTROL, NOCONTROL,NOCONTROL);
}


// ------------------------------------------------------
//					EliminateRollover
// ------------------------------------------------------
int EliminateRollover(int currEncoder, int preEncoder, int encoderDir)
{
	int diffEncoder = (currEncoder - preEncoder);	//As robot go forward, left encoder decreases and 

																//Right encoder increases...
	
	if(((diffEncoder) > 10000)||((diffEncoder) <-10000))
	{
		if(diffEncoder<0)
		
			diffEncoder=(cFULL_COUNT-preEncoder+currEncoder+1);
		
		else
			diffEncoder=-(cFULL_COUNT-currEncoder+preEncoder+1);
	}
	else
	{
		//return diffEncoder;
	}
	
	
	return diffEncoder;
}

// ------------------------------------------------------(1)
//					GetDeltaDisplacement
// ------------------------------------------------------
double GetDeltaDisplacement(int dEncoder1,int dEncoder2)
{
	
	double dispLeft		= ENCODER_SCALAR_H20*dEncoder1;	
	double dispRight	= ENCODER_SCALAR_H20*dEncoder2;

	return (dispLeft+dispRight)/2;
	
}

//-------------------------------------------------------(2)
//					Robot Velocity Profiles
//-------------------------------------------------------
double get_velocity(double Vx, double Vy, double Theta)
{

	Vxy=sqrt (Vx*Vx+Vy*Vy);

}
// ------------------------------------------------------(3)
//					GetDeltaAngle
// ------------------------------------------------------
double GetDeltaAngle(int diffEncoder1,int diffEncoder2)
{
	double dispLeft		= ENCODER_SCALAR_H20*diffEncoder1;	
	double dispRight	= ENCODER_SCALAR_H20*diffEncoder2;	

	return ((-dispLeft+dispRight)/TRACK);
}
//-------------------------------------------------------(4)
//					Control wheel Velocity Profiles
//-------------------------------------------------------
double control_wheel_velocity(double w_left_d,double w_right_d,int LeftwheelW,int RightwheelW )
{

	
	double KwP=21;
	double KwD=4;
	double KwI=7;
	/*
	Wheel_1_velocity[3]=Wheel_1_velocity[2];
	Wheel_1_velocity[2]=Wheel_1_velocity[1];
	Wheel_1_velocity[1]=LeftwheelW;
	
	LeftwheelW =(Wheel_1_velocity[1]+Wheel_1_velocity[2]+Wheel_1_velocity[3])/3;
	
	Wheel_2_velocity[3]=Wheel_2_velocity[2];
	Wheel_2_velocity[2]=Wheel_2_velocity[1];
	Wheel_2_velocity[1]=RightwheelW ;
	
	RightwheelW=(Wheel_2_velocity[1]+Wheel_2_velocity[2]+Wheel_2_velocity[3])/3;
	//******************************************************************
		w_pre_left_wheel=w_left_wheel;
		w_pre_right_wheel=w_right_wheel;
		
		w_left_wheel=LeftwheelW;//publishing
		w_right_wheel=RightwheelW;
		*/
	//******************************************************************
	
	int w_left_error_D=0;
	int w_right_error_D=0;
	
	int w_left_error=w_left_d-LeftwheelW;
	int w_right_error=w_right_d-RightwheelW;
	
	if(abs(w_left_error-W_left_wheel_error_Previous)<100) w_left_error_D=(w_left_error-W_left_wheel_error_Previous)/dt; //avoid startup impulse
	if(abs(w_right_error-W_right_wheel_error_Previous)<100) w_right_error_D=(w_right_error-W_right_wheel_error_Previous)/dt;
	
	
	W_left_wheel_error_Previous=w_left_error;
	W_right_wheel_error_Previous=w_right_error;
	
	W_left_wheel_error_I=W_left_wheel_error_I+w_left_error*dt;
	W_right_wheel_error_I=W_right_wheel_error_I+w_right_error*dt;
	
if(w_left_d>0){
	left_PWM=KwI*W_left_wheel_error_I+KwP*w_left_error+KwD*w_left_error_D+21000;
	if(left_PWM>27000)left_PWM=27000;
    }
else if (w_left_d<0){
	left_PWM=KwI*W_left_wheel_error_I+KwP*w_left_error+KwD*w_left_error_D+12000;
	if(left_PWM<6000)left_PWM=6000;
	}
else {
	left_PWM=16384;
	}
	
if(w_right_d>0){
	right_PWM=-KwI*W_right_wheel_error_I-KwP*w_right_error-KwD*w_right_error_D+12000;
	if(right_PWM<6000)right_PWM=6000;
	}
else if(w_right_d<0){
	right_PWM=-KwI*W_right_wheel_error_I-KwP*w_right_error-KwD*w_right_error_D+21000;
	if(right_PWM>27000)right_PWM=27000;
	}
else{
	right_PWM=16384;
    }
	
	

}
//-------------------------------------------------------------------(5)
//					wheel filter
//----------------------------------------------------------------------
void wheel_filter(int diffEncoder1,int diffEncoder2,int W_wheel_1,int W_wheel_2){
	
	Wheel_1_velocity[3]=Wheel_1_velocity[2];
	Wheel_1_velocity[2]=Wheel_1_velocity[1];
	Wheel_1_velocity[1]=W_wheel_1;
	
	W_wheel_1 =(Wheel_1_velocity[1]+Wheel_1_velocity[2]+Wheel_1_velocity[3])/3;
	
	Wheel_2_velocity[3]=Wheel_2_velocity[2];
	Wheel_2_velocity[2]=Wheel_2_velocity[1];
	Wheel_2_velocity[1]=W_wheel_2 ;
	
	W_wheel_2=(Wheel_2_velocity[1]+Wheel_2_velocity[2]+Wheel_2_velocity[3])/3;
	//******************************************************************
		w_pre_left_wheel=w_left_wheel;
		w_pre_right_wheel=w_right_wheel;
		
		w_left_wheel=W_wheel_1;
		w_right_wheel=W_wheel_2;
	//******************************************************************
	int D_encorder1_predicted=w_pre_left_wheel*dt;
	int D_encorder2_predicted=w_pre_right_wheel*dt;
	//******************************************************************

	 
	if(((abs(diffEncoder1-D_encorder1))>0)||((abs(D_encorder1_predicted-D_encorder1))>0)){
	  K_e_l=pow((diffEncoder1-D_encorder1),2.0)/(pow((diffEncoder1-D_encorder1),2.0)+pow((D_encorder1_predicted-D_encorder1),2.0));
	}
	
	if(((abs(diffEncoder2-D_encorder2))>0)||((abs(D_encorder2_predicted-D_encorder2))>0)){
	  K_e_r=pow((diffEncoder2-D_encorder2),2.0)/(pow((diffEncoder2-D_encorder2),2.0)+pow((D_encorder2_predicted-D_encorder2),2.0));
	}
	
	D_encorder1=(1-K_e_l)*diffEncoder1+K_e_l*D_encorder1_predicted;
	D_encorder2=(1-K_e_r)*diffEncoder2+K_e_r*D_encorder2_predicted;
	
	//gvariable0=x;//D_encorder1_predicted;
	//gvariable1=y;//D_encorder1;
	//gvariable2=theta*180/pi;//diffEncoder1;
}
//-------------------------------------------------------------------(6)
//					Update Parameters
//-------------------------------------------------------
double update_parameters()
{			
			Vx = (x - x_1)/dt;
			Vy = (y - y_1)/dt;
			Vz = deltaTheta;//(theta - theta_1)/dt;
			robotVx=deltaD/dt;
	
	x_1			= x;
	y_1			= y;
	theta_1		= theta;
	
	/*
			x_coordinates_error=g_coordinates_x-x;
			y_coordinates_error=g_coordinates_y-y;
		
			p=sqrt(x_coordinates_error*x_coordinates_error+y_coordinates_error*y_coordinates_error);
			p_dot=(p-previous_p)/dt;
			previous_p=p;
			

			beta=atan2(g_coordinates_y-y,g_coordinates_x-x);
			
			alpha=beta-theta;
			alpha_dot=(alpha-previous_alpha)/dt;
			previous_alpha=alpha;
			alpha_I=alpha_I+alpha*dt;
			
			p_dot=(p-previous_p)/dt;
			previous_p=p;
			
			*/
}

// -------------------------------------------------------------------(6)
//					ComputeSteering
// ------------------------------------------------------
void ComputeSteering(int tempEncoder1,int tempEncoder2,int wheel_1_Vel,int wheel_2_Vel,int tempEncoderDir1,int tempEncoderDir2)
{
	loopcount++;
	if(loopcount>10000)loopcount=10000;


	tempEncoderDir2		= -1*tempEncoderDir2;		//To get the same direction as encoder2
	
	int diffEncoder11	= EliminateRollover(tempEncoder1,preEncoder1,tempEncoderDir1);
	int diffEncoder22	= EliminateRollover(tempEncoder2,preEncoder2,tempEncoderDir2);
	
	encoder1		= tempEncoder1;
	encoder2		= tempEncoder2;
//---------------------------------------------------------
    
	if(loopcount>5){
	encoderLeft=encoderLeft+diffEncoder11;
	encoderRight=encoderRight+diffEncoder22;
	
	encoderDir_L= tempEncoderDir1;
	encoderDir_R=tempEncoderDir2;
	
	encoder_difference= encoderLeft-encoderRight; 
	
    //rate_encorder_difference=encoder_difference-pre_encorder_difference;
    //pre_encorder_difference=encoder_difference;

	wheel_filter(diffEncoder11,-diffEncoder22,tempEncoderDir1*wheel_1_Vel,tempEncoderDir2*wheel_2_Vel);
	
	deltaD		= GetDeltaDisplacement(D_encorder1,D_encorder2);
	deltaTheta	= GetDeltaAngle(D_encorder1,D_encorder2);

	control_wheel_velocity(w_left*375/(2*M_PI),w_right*375/(2*M_PI),w_left_wheel,w_right_wheel);
    //temp_encorderLeft=encoderLeft;
    //temp_encorderRight=encoderRight;


		}
		
	preEncoder1		= tempEncoder1;
	preEncoder2		= tempEncoder2;
	
//-----------------------------------------time calculation
	current_time = ros::Time::now();		
	dt = (current_time - last_time).toSec();
	last_time	= current_time;
//---------------------------------------------------------


	if(initial<4)
	{
		deltaD		= 0;
		deltaTheta	= 0;
		
		initial++;
	}
		
	rotational_theta =rotational_theta+ deltaTheta;  
	
	if(rotational_theta>=0){
	theta=rotational_theta+pi;
	theta=fmod(theta, 2*pi)-pi;
	}
	
	else {
		theta			=rotational_theta-pi;		
		theta=fmod(theta, 2*pi)+pi;
	}

	if(deltaTheta == 0)
	{
		x				= x_1 + deltaD*cos(theta);
		y				= y_1 + deltaD*sin(theta);
	}
	else
	{
		x				= x_1 + deltaD*cos(theta + deltaTheta/2)*sin(deltaTheta/2)/(deltaTheta/2);
		y				= y_1 + deltaD*sin(theta + deltaTheta/2)*sin(deltaTheta/2)/(deltaTheta/2);
	}
	
//--------------------------------------------------------------------------------------------------------



			//since all odometry is 6DOF we'll need a quaternion created from yaw
			//geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(theta);

			//first, we'll publish the transform over tf
			geometry_msgs::TransformStamped odom_trans;
			odom_trans.header.stamp = current_time;
			odom_trans.header.frame_id = "odom";
			odom_trans.child_frame_id = "base_link";

			odom_trans.transform.translation.x = x;
			odom_trans.transform.translation.y = y;
			odom_trans.transform.translation.z = 0.0;
			odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(theta);

			//send the transform
			odom_broadcaster.sendTransform(odom_trans);

			//next, we'll publish the odometry message over ROS
			nav_msgs::Odometry odom;
			odom.header.stamp = current_time;
			odom.header.frame_id = "odom";

			//set the position
			odom.pose.pose.position.x = x;
			odom.pose.pose.position.y = y;
			odom.pose.pose.position.z = 0.0;
			odom.pose.pose.orientation = tf::createQuaternionMsgFromYaw(theta);

			//set the velocity
			
			odom.child_frame_id = "base_link";
			odom.twist.twist.linear.x = robotVx;
			odom.twist.twist.linear.y = 0;
			odom.twist.twist.angular.z = Vz;
			
			//publish the message
			odom_pub_.publish(odom);
	
			ROS_DEBUG("Current pose: x=%f, y=%f, theta=%f\n",x,y,theta*180/3.14);
			
	scanpose[0]=x;
	scanpose[1]=y;
	scanpose[2]=theta;
	scanpose[3]=D_encorder1;
	scanpose[4]=D_encorder2;
			
	//printf("Encoder readings: %d, %d\n",tempEncoder1,tempEncoder2);
	//printf("Encoder readings: %d, %d\n",tempEncoderDir1,tempEncoderDir2);
//--------------------------------------------------------------------------------------------------------------
//since all odometry is 6DOF we'll need a quaternion created from yaw
/*
			geometry_msgs::Quaternion path_quat = tf::createQuaternionMsgFromYaw(theta);

			//first, we'll publish the transform over tf
			geometry_msgs::TransformStamped path_trans;
			path_trans.header.stamp = current_time;
			path_trans.header.frame_id = "path";
			path_trans.child_frame_id = "base_link";

			path_trans.transform.translation.x = x;
			path_trans.transform.translation.y = y;
			path_trans.transform.translation.z = 0.0;
			path_trans.transform.rotation = path_quat;

			//send the transform
			path_broadcaster.sendTransform(path_trans);


			//next, we'll publish the odometry message over ROS
			nav_msgs::Path path;
		
			   path.poses.resize(1);
		      for (uint32_t i = 0 ; i < 1; ++i)
		      {
				path.header.stamp = current_time;
				path.header.frame_id = string("path");
				
				path.poses[i].header.stamp = current_time;
				path.poses[i].header.frame_id = string("path");
			//set the position
				path.poses[i].pose.position.x = x;			
				path.poses[i].pose.position.y = y;
				path.poses[i].pose.position.z = 0.0;
				path.poses[i].pose.orientation = path_quat;					
		      }
		      
			//publish the message
			path_pub_.publish(path);

			/*
			      rangerArray.ranges.resize(IR_NUM);
		      for (uint32_t i = 0 ; i < IR_NUM; ++i)
		      {
		          rangerArray.ranges[i].header.stamp = ros::Time::now();
		          rangerArray.ranges[i].header.frame_id = string("drrobot_ir_");
		          rangerArray.ranges[i].header.frame_id += boost::lexical_cast<std::string>(i);
		          rangerArray.ranges[i].range = ad2Dis(rangeSensorData_.irRangeSensor[i]);
		          rangerArray.ranges[i].radiation_type = drrobot_jaguar4x4_player::Range::INFRARED;
		      }

		      ir_pub_.publish(rangerArray);

			*/
		//publish encorder displacemet to record for EKF implementation
publish_encorder();
publish_Rscanpose();
}


private:

    DrRobotMotionSensorDriver* drrobotMotionDriver_;
    DrRobotMotionSensorDriver* drrobotPowerDriver_;
    struct DrRobotMotionConfig robotConfig1_;
    struct DrRobotMotionConfig robotConfig2_;

    std::string odom_frame_id_;
    struct MotorSensorData motorSensorData_;
    struct RangeSensorData rangeSensorData_;
    struct PowerSensorData powerSensorData_;
    struct StandardSensorData standardSensorData_;
    struct CustomSensorData customSensorData_;

	tf::TransformBroadcaster broadcaster_;

    std::string robotType_;
    std::string robotID_;
    std::string robotIP_;
    std::string robotCommMethod_;
    std::string robotSerialPort_;
    bool enable_ir_;
    bool enable_sonar_;
    int  commPortNum_;
    int  encoderOneCircleCnt_;
    double wheelDis_;
    double wheelRadius_;
    int motorDir_;
    double minSpeed_;
    double maxSpeed_;


    int cntNum_;
    double ad2Dis(int adValue)
    {
      double temp = 0;
      double irad2Dis = 0;

      if (adValue <= 0)
        temp = -1;
      else
        temp = 21.6 /((double)adValue * 3 /4096 - 0.17);

      if ( (temp > 80) || (temp < 0))
      {
        irad2Dis = 0.81;
      }
      else if( (temp < 10) && (temp > 0))
      {
        irad2Dis = 0.09;
      }
      else
        irad2Dis = temp /100;
      return irad2Dis;
    }
};

//======================================================================MAIN=========================

int main(int argc, char** argv)
{

	
	
    ros::init(argc, argv, "drrobot_jaguar4x4_player");

    DrRobotPlayerNode drrobotPlayer;
    ros::NodeHandle n;
    

    // Start up the robot
    if (drrobotPlayer.start() != 0)
    {
        exit(-1);
    }
    /////////////////////////////////////////////////////////////////

    ros::Rate loop_rate(10);      //10Hz


    while (n.ok())
    {
      drrobotPlayer.doUpdate();
      ROS_INFO("Gayan Package");
      drrobotPlayer.sendTransform();
      ros::spinOnce();
     loop_rate.sleep();
    }
    /////////////////////////////////////////////////////////////////

    // Stop the robot
    drrobotPlayer.stop();

    return(0);
}
