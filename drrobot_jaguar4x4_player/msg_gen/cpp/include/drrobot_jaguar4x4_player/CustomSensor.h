/* Auto-generated by genmsg_cpp for file /home/bgs/catkin_ws/H20_motion/drrobot_jaguar4x4_player/msg/CustomSensor.msg */
#ifndef DRROBOT_JAGUAR4X4_PLAYER_MESSAGE_CUSTOMSENSOR_H
#define DRROBOT_JAGUAR4X4_PLAYER_MESSAGE_CUSTOMSENSOR_H
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
struct CustomSensor_ {
  typedef CustomSensor_<ContainerAllocator> Type;

  CustomSensor_()
  : header()
  , robot_type()
  , customADData()
  , customIO(0)
  {
  }

  CustomSensor_(const ContainerAllocator& _alloc)
  : header(_alloc)
  , robot_type(_alloc)
  , customADData(_alloc)
  , customIO(0)
  {
  }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
   ::std_msgs::Header_<ContainerAllocator>  header;

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _robot_type_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  robot_type;

  typedef std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  _customADData_type;
  std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  customADData;

  typedef uint8_t _customIO_type;
  uint8_t customIO;


  typedef boost::shared_ptr< ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator>  const> ConstPtr;
}; // struct CustomSensor
typedef  ::drrobot_jaguar4x4_player::CustomSensor_<std::allocator<void> > CustomSensor;

typedef boost::shared_ptr< ::drrobot_jaguar4x4_player::CustomSensor> CustomSensorPtr;
typedef boost::shared_ptr< ::drrobot_jaguar4x4_player::CustomSensor const> CustomSensorConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace drrobot_jaguar4x4_player

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> > {
  static const char* value() 
  {
    return "99688dde61b19bf7f23d2791779ffdd3";
  }

  static const char* value(const  ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x99688dde61b19bf7ULL;
  static const uint64_t static_value2 = 0xf23d2791779ffdd3ULL;
};

template<class ContainerAllocator>
struct DataType< ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> > {
  static const char* value() 
  {
    return "drrobot_jaguar4x4_player/CustomSensor";
  }

  static const char* value(const  ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# custom Sensor information message from DrRobot Robot.\n\
\n\
Header header    	# timestamp in the header is the time the driver\n\
		 	# returned the battery/power reading\n\
string robot_type	# robot type, I90 series, sentinel3 or Hawk/H20 Power/Motion\n\
\n\
#make sure what sensor is on your expanded sensor port\n\
uint32[] customADData		# custom AD channel 8 channel on the board, which channel is avaiable please contact Dr Robot\n\
uint8 customIO    #expanded IO\n\
\n\
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

  static const char* value(const  ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct HasHeader< ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct HasHeader< const ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.header);
    stream.next(m.robot_type);
    stream.next(m.customADData);
    stream.next(m.customIO);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER
}; // struct CustomSensor_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::drrobot_jaguar4x4_player::CustomSensor_<ContainerAllocator> & v) 
  {
    s << indent << "header: ";
s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "robot_type: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.robot_type);
    s << indent << "customADData[]" << std::endl;
    for (size_t i = 0; i < v.customADData.size(); ++i)
    {
      s << indent << "  customADData[" << i << "]: ";
      Printer<uint32_t>::stream(s, indent + "  ", v.customADData[i]);
    }
    s << indent << "customIO: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.customIO);
  }
};


} // namespace message_operations
} // namespace ros

#endif // DRROBOT_JAGUAR4X4_PLAYER_MESSAGE_CUSTOMSENSOR_H

