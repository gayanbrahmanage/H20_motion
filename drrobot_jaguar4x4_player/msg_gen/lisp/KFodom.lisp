; Auto-generated. Do not edit!


(cl:in-package drrobot_jaguar4x4_player-msg)


;//! \htmlinclude KFodom.msg.html

(cl:defclass <KFodom> (roslisp-msg-protocol:ros-message)
  ((deltaD
    :reader deltaD
    :initarg :deltaD
    :type cl:float
    :initform 0.0)
   (deltatheta
    :reader deltatheta
    :initarg :deltatheta
    :type cl:float
    :initform 0.0)
   (Ddot
    :reader Ddot
    :initarg :Ddot
    :type cl:float
    :initform 0.0)
   (thetadot
    :reader thetadot
    :initarg :thetadot
    :type cl:float
    :initform 0.0))
)

(cl:defclass KFodom (<KFodom>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <KFodom>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'KFodom)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name drrobot_jaguar4x4_player-msg:<KFodom> is deprecated: use drrobot_jaguar4x4_player-msg:KFodom instead.")))

(cl:ensure-generic-function 'deltaD-val :lambda-list '(m))
(cl:defmethod deltaD-val ((m <KFodom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drrobot_jaguar4x4_player-msg:deltaD-val is deprecated.  Use drrobot_jaguar4x4_player-msg:deltaD instead.")
  (deltaD m))

(cl:ensure-generic-function 'deltatheta-val :lambda-list '(m))
(cl:defmethod deltatheta-val ((m <KFodom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drrobot_jaguar4x4_player-msg:deltatheta-val is deprecated.  Use drrobot_jaguar4x4_player-msg:deltatheta instead.")
  (deltatheta m))

(cl:ensure-generic-function 'Ddot-val :lambda-list '(m))
(cl:defmethod Ddot-val ((m <KFodom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drrobot_jaguar4x4_player-msg:Ddot-val is deprecated.  Use drrobot_jaguar4x4_player-msg:Ddot instead.")
  (Ddot m))

(cl:ensure-generic-function 'thetadot-val :lambda-list '(m))
(cl:defmethod thetadot-val ((m <KFodom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drrobot_jaguar4x4_player-msg:thetadot-val is deprecated.  Use drrobot_jaguar4x4_player-msg:thetadot instead.")
  (thetadot m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <KFodom>) ostream)
  "Serializes a message object of type '<KFodom>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'deltaD))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'deltatheta))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Ddot))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'thetadot))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <KFodom>) istream)
  "Deserializes a message object of type '<KFodom>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'deltaD) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'deltatheta) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Ddot) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'thetadot) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<KFodom>)))
  "Returns string type for a message object of type '<KFodom>"
  "drrobot_jaguar4x4_player/KFodom")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'KFodom)))
  "Returns string type for a message object of type 'KFodom"
  "drrobot_jaguar4x4_player/KFodom")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<KFodom>)))
  "Returns md5sum for a message object of type '<KFodom>"
  "dbaa4aa231e888ba44311921aa92587c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'KFodom)))
  "Returns md5sum for a message object of type 'KFodom"
  "dbaa4aa231e888ba44311921aa92587c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<KFodom>)))
  "Returns full string definition for message of type '<KFodom>"
  (cl:format cl:nil "float32 deltaD~%float32 deltatheta~%float32 Ddot~%float32 thetadot~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'KFodom)))
  "Returns full string definition for message of type 'KFodom"
  (cl:format cl:nil "float32 deltaD~%float32 deltatheta~%float32 Ddot~%float32 thetadot~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <KFodom>))
  (cl:+ 0
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <KFodom>))
  "Converts a ROS message object to a list"
  (cl:list 'KFodom
    (cl:cons ':deltaD (deltaD msg))
    (cl:cons ':deltatheta (deltatheta msg))
    (cl:cons ':Ddot (Ddot msg))
    (cl:cons ':thetadot (thetadot msg))
))
