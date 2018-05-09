/* Auto-generated by genmsg_cpp for file /home/bgs/catkin_ws/H20_motion/drrobot_jaguar4x4_player/msg/MotorInfoArray.msg */
#ifndef DRROBOT_JAGUAR4X4_PLAYER_MESSAGE_MOTORINFOARRAY_H
#define DRROBOT_JAGUAR4X4_PLAYER_MESSAGE_MOTORINFOARRAY_H
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

#include "drrobot_jaguar4x4_player/MotorInfo.h"

namespace drrobot_jaguar4x4_player
{
template <class ContainerAllocator>
struct MotorInfoArray_ {
  typedef MotorInfoArray_<ContainerAllocator> Type;

  MotorInfoArray_()
  : motorInfos()
  {
  }

  MotorInfoArray_(const ContainerAllocator& _alloc)
  : motorInfos(_alloc)
  {
  }

  typedef std::vector< ::drrobot_jaguar4x4_player::MotorInfo_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::drrobot_jaguar4x4_player::MotorInfo_<ContainerAllocator> >::other >  _motorInfos_type;
  std::vector< ::drrobot_jaguar4x4_player::MotorInfo_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::drrobot_jaguar4x4_player::MotorInfo_<ContainerAllocator> >::other >  motorInfos;


  typedef boost::shared_ptr< ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator>  const> ConstPtr;
}; // struct MotorInfoArray
typedef  ::drrobot_jaguar4x4_player::MotorInfoArray_<std::allocator<void> > MotorInfoArray;

typedef boost::shared_ptr< ::drrobot_jaguar4x4_player::MotorInfoArray> MotorInfoArrayPtr;
typedef boost::shared_ptr< ::drrobot_jaguar4x4_player::MotorInfoArray const> MotorInfoArrayConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace drrobot_jaguar4x4_player

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator> > {
  static const char* value() 
  {
    return "64d8eb9826ec2f78779f54df29bcc931";
  }

  static const char* value(const  ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x64d8eb9826ec2f78ULL;
  static const uint64_t static_value2 = 0x779f54df29bcc931ULL;
};

template<class ContainerAllocator>
struct DataType< ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator> > {
  static const char* value() 
  {
    return "drrobot_jaguar4x4_player/MotorInfoArray";
  }

  static const char* value(const  ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator> > {
  static const char* value() 
  {
    return "#this message will be used for motor sensor\n\
MotorInfo[] motorInfos\n\
\n\
================================================================================\n\
MSG: drrobot_jaguar4x4_player/MotorInfo\n\
# motor sensor data message from DrRobot Robot.\n\
\n\
Header header    	# timestamp in the header is the time the driver\n\
		 	# returned the battery/power reading\n\
string robot_type	# robot type, I90 series, sentinel3 or Jaguar Power/Motion\n\
\n\
uint32 encoder_pos	# encoder positon count\n\
uint32 encoder_vel	# encoder velocity value\n\
uint32 encoder_dir	# encoder direction\n\
\n\
float32 motor_current	# motor current\n\
uint32 motor_pwm	# output PWM value, only for Jaguar series robot\n\
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

  static const char* value(const  ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.motorInfos);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER
}; // struct MotorInfoArray_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::drrobot_jaguar4x4_player::MotorInfoArray_<ContainerAllocator> & v) 
  {
    s << indent << "motorInfos[]" << std::endl;
    for (size_t i = 0; i < v.motorInfos.size(); ++i)
    {
      s << indent << "  motorInfos[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::drrobot_jaguar4x4_player::MotorInfo_<ContainerAllocator> >::stream(s, indent + "    ", v.motorInfos[i]);
    }
  }
};


} // namespace message_operations
} // namespace ros

#endif // DRROBOT_JAGUAR4X4_PLAYER_MESSAGE_MOTORINFOARRAY_H

