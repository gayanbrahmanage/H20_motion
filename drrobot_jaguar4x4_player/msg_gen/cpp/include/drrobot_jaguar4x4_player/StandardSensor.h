/* Auto-generated by genmsg_cpp for file /home/bgs/catkin_ws/H20_motion/drrobot_jaguar4x4_player/msg/StandardSensor.msg */
#ifndef DRROBOT_JAGUAR4X4_PLAYER_MESSAGE_STANDARDSENSOR_H
#define DRROBOT_JAGUAR4X4_PLAYER_MESSAGE_STANDARDSENSOR_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "std_msgs/Header.h"

namespace drrobot_jaguar4x4_player
{
template <class ContainerAllocator>
struct StandardSensor_ {
  typedef StandardSensor_<ContainerAllocator> Type;

  StandardSensor_()
  : header()
  , robot_type()
  , humanSensorData()
  , tiltingSensorData()
  , overHeatSensorData()
  , thermoSensorData(0)
  , boardPowerVol(0.0)
  , motorPowerVol(0.0)
  , servoPowerVol(0.0)
  , refVol(0.0)
  , potVol(0.0)
  {
  }

  StandardSensor_(const ContainerAllocator& _alloc)
  : header(_alloc)
  , robot_type(_alloc)
  , humanSensorData(_alloc)
  , tiltingSensorData(_alloc)
  , overHeatSensorData(_alloc)
  , thermoSensorData(0)
  , boardPowerVol(0.0)
  , motorPowerVol(0.0)
  , servoPowerVol(0.0)
  , refVol(0.0)
  , potVol(0.0)
  {
  }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
   ::std_msgs::Header_<ContainerAllocator>  header;

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _robot_type_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  robot_type;

  typedef std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  _humanSensorData_type;
  std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  humanSensorData;

  typedef std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  _tiltingSensorData_type;
  std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  tiltingSensorData;

  typedef std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  _overHeatSensorData_type;
  std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  overHeatSensorData;

  typedef uint32_t _thermoSensorData_type;
  uint32_t thermoSensorData;

  typedef float _boardPowerVol_type;
  float boardPowerVol;

  typedef float _motorPowerVol_type;
  float motorPowerVol;

  typedef float _servoPowerVol_type;
  float servoPowerVol;

  typedef float _refVol_type;
  float refVol;

  typedef float _potVol_type;
  float potVol;


  typedef boost::shared_ptr< ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator>  const> ConstPtr;
}; // struct StandardSensor
typedef  ::drrobot_jaguar4x4_player::StandardSensor_<std::allocator<void> > StandardSensor;

typedef boost::shared_ptr< ::drrobot_jaguar4x4_player::StandardSensor> StandardSensorPtr;
typedef boost::shared_ptr< ::drrobot_jaguar4x4_player::StandardSensor const> StandardSensorConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace drrobot_jaguar4x4_player

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> > {
  static const char* value() 
  {
    return "e867c61af4cf779989629edb31d6fbd8";
  }

  static const char* value(const  ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xe867c61af4cf7799ULL;
  static const uint64_t static_value2 = 0x89629edb31d6fbd8ULL;
};

template<class ContainerAllocator>
struct DataType< ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> > {
  static const char* value() 
  {
    return "drrobot_jaguar4x4_player/StandardSensor";
  }

  static const char* value(const  ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# standard Sensor information message from DrRobot Robot.\n\
\n\
Header header    	# timestamp in the header is the time the driver\n\
		 	# returned the battery/power reading\n\
string robot_type	# robot type, I90 series, sentinel3 or Hawk/H20 Power/Motion\n\
\n\
#make sure below sensors on your robot or not\n\
uint32[] humanSensorData		#human sensor\n\
uint32[] tiltingSensorData    #tilting sensor X Y\n\
uint32[] overHeatSensorData   # over heat sensor on the board\n\
uint32 thermoSensorData	    # enviroment temperature\n\
float32 boardPowerVol 			# control board voltage\n\
float32 motorPowerVol			# motor power voltage\n\
float32 servoPowerVol			# servo power voltage\n\
float32 refVol					# AD reference voltage\n\
float32 potVol					# potentialmeter power voltage , not used now\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
";
  }

  static const char* value(const  ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct HasHeader< ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct HasHeader< const ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.header);
    stream.next(m.robot_type);
    stream.next(m.humanSensorData);
    stream.next(m.tiltingSensorData);
    stream.next(m.overHeatSensorData);
    stream.next(m.thermoSensorData);
    stream.next(m.boardPowerVol);
    stream.next(m.motorPowerVol);
    stream.next(m.servoPowerVol);
    stream.next(m.refVol);
    stream.next(m.potVol);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER
}; // struct StandardSensor_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::drrobot_jaguar4x4_player::StandardSensor_<ContainerAllocator> & v) 
  {
    s << indent << "header: ";
s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "robot_type: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.robot_type);
    s << indent << "humanSensorData[]" << std::endl;
    for (size_t i = 0; i < v.humanSensorData.size(); ++i)
    {
      s << indent << "  humanSensorData[" << i << "]: ";
      Printer<uint32_t>::stream(s, indent + "  ", v.humanSensorData[i]);
    }
    s << indent << "tiltingSensorData[]" << std::endl;
    for (size_t i = 0; i < v.tiltingSensorData.size(); ++i)
    {
      s << indent << "  tiltingSensorData[" << i << "]: ";
      Printer<uint32_t>::stream(s, indent + "  ", v.tiltingSensorData[i]);
    }
    s << indent << "overHeatSensorData[]" << std::endl;
    for (size_t i = 0; i < v.overHeatSensorData.size(); ++i)
    {
      s << indent << "  overHeatSensorData[" << i << "]: ";
      Printer<uint32_t>::stream(s, indent + "  ", v.overHeatSensorData[i]);
    }
    s << indent << "thermoSensorData: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.thermoSensorData);
    s << indent << "boardPowerVol: ";
    Printer<float>::stream(s, indent + "  ", v.boardPowerVol);
    s << indent << "motorPowerVol: ";
    Printer<float>::stream(s, indent + "  ", v.motorPowerVol);
    s << indent << "servoPowerVol: ";
    Printer<float>::stream(s, indent + "  ", v.servoPowerVol);
    s << indent << "refVol: ";
    Printer<float>::stream(s, indent + "  ", v.refVol);
    s << indent << "potVol: ";
    Printer<float>::stream(s, indent + "  ", v.potVol);
  }
};


} // namespace message_operations
} // namespace ros

#endif // DRROBOT_JAGUAR4X4_PLAYER_MESSAGE_STANDARDSENSOR_H

