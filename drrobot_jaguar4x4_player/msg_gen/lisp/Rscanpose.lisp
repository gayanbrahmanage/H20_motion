; Auto-generated. Do not edit!


(cl:in-package drrobot_jaguar4x4_player-msg)


;//! \htmlinclude Rscanpose.msg.html

(cl:defclass <Rscanpose> (roslisp-msg-protocol:ros-message)
  ((Rscanpose
    :reader Rscanpose
    :initarg :Rscanpose
    :type (cl:vector cl:float)
   :initform (cl:make-array 645 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass Rscanpose (<Rscanpose>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Rscanpose>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Rscanpose)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name drrobot_jaguar4x4_player-msg:<Rscanpose> is deprecated: use drrobot_jaguar4x4_player-msg:Rscanpose instead.")))

(cl:ensure-generic-function 'Rscanpose-val :lambda-list '(m))
(cl:defmethod Rscanpose-val ((m <Rscanpose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drrobot_jaguar4x4_player-msg:Rscanpose-val is deprecated.  Use drrobot_jaguar4x4_player-msg:Rscanpose instead.")
  (Rscanpose m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Rscanpose>) ostream)
  "Serializes a message object of type '<Rscanpose>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'Rscanpose))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Rscanpose>) istream)
  "Deserializes a message object of type '<Rscanpose>"
  (cl:setf (cl:slot-value msg 'Rscanpose) (cl:make-array 645))
  (cl:let ((vals (cl:slot-value msg 'Rscanpose)))
    (cl:dotimes (i 645)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Rscanpose>)))
  "Returns string type for a message object of type '<Rscanpose>"
  "drrobot_jaguar4x4_player/Rscanpose")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Rscanpose)))
  "Returns string type for a message object of type 'Rscanpose"
  "drrobot_jaguar4x4_player/Rscanpose")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Rscanpose>)))
  "Returns md5sum for a message object of type '<Rscanpose>"
  "1b2170f99f4bd314082e9742552d3d71")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Rscanpose)))
  "Returns md5sum for a message object of type 'Rscanpose"
  "1b2170f99f4bd314082e9742552d3d71")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Rscanpose>)))
  "Returns full string definition for message of type '<Rscanpose>"
  (cl:format cl:nil "float32[645] Rscanpose~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Rscanpose)))
  "Returns full string definition for message of type 'Rscanpose"
  (cl:format cl:nil "float32[645] Rscanpose~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Rscanpose>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'Rscanpose) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Rscanpose>))
  "Converts a ROS message object to a list"
  (cl:list 'Rscanpose
    (cl:cons ':Rscanpose (Rscanpose msg))
))
