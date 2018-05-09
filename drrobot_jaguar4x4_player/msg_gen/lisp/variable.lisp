; Auto-generated. Do not edit!


(cl:in-package drrobot_jaguar4x4_player-msg)


;//! \htmlinclude variable.msg.html

(cl:defclass <variable> (roslisp-msg-protocol:ros-message)
  ((variable0
    :reader variable0
    :initarg :variable0
    :type cl:float
    :initform 0.0)
   (variable1
    :reader variable1
    :initarg :variable1
    :type cl:float
    :initform 0.0)
   (variable2
    :reader variable2
    :initarg :variable2
    :type cl:float
    :initform 0.0))
)

(cl:defclass variable (<variable>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <variable>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'variable)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name drrobot_jaguar4x4_player-msg:<variable> is deprecated: use drrobot_jaguar4x4_player-msg:variable instead.")))

(cl:ensure-generic-function 'variable0-val :lambda-list '(m))
(cl:defmethod variable0-val ((m <variable>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drrobot_jaguar4x4_player-msg:variable0-val is deprecated.  Use drrobot_jaguar4x4_player-msg:variable0 instead.")
  (variable0 m))

(cl:ensure-generic-function 'variable1-val :lambda-list '(m))
(cl:defmethod variable1-val ((m <variable>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drrobot_jaguar4x4_player-msg:variable1-val is deprecated.  Use drrobot_jaguar4x4_player-msg:variable1 instead.")
  (variable1 m))

(cl:ensure-generic-function 'variable2-val :lambda-list '(m))
(cl:defmethod variable2-val ((m <variable>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drrobot_jaguar4x4_player-msg:variable2-val is deprecated.  Use drrobot_jaguar4x4_player-msg:variable2 instead.")
  (variable2 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <variable>) ostream)
  "Serializes a message object of type '<variable>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'variable0))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'variable1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'variable2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <variable>) istream)
  "Deserializes a message object of type '<variable>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'variable0) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'variable1) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'variable2) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<variable>)))
  "Returns string type for a message object of type '<variable>"
  "drrobot_jaguar4x4_player/variable")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'variable)))
  "Returns string type for a message object of type 'variable"
  "drrobot_jaguar4x4_player/variable")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<variable>)))
  "Returns md5sum for a message object of type '<variable>"
  "58885270dd0a2390053b2e1182f5e840")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'variable)))
  "Returns md5sum for a message object of type 'variable"
  "58885270dd0a2390053b2e1182f5e840")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<variable>)))
  "Returns full string definition for message of type '<variable>"
  (cl:format cl:nil "float32 variable0~%float32 variable1~%float32 variable2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'variable)))
  "Returns full string definition for message of type 'variable"
  (cl:format cl:nil "float32 variable0~%float32 variable1~%float32 variable2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <variable>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <variable>))
  "Converts a ROS message object to a list"
  (cl:list 'variable
    (cl:cons ':variable0 (variable0 msg))
    (cl:cons ':variable1 (variable1 msg))
    (cl:cons ':variable2 (variable2 msg))
))
