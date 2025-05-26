; Auto-generated. Do not edit!


(cl:in-package test_pub_sub_protobuf-msg)


;//! \htmlinclude Chatter.msg.html

(cl:defclass <Chatter> (roslisp-msg-protocol:ros-message)
  ((message
    :reader message
    :initarg :message
    :type cl:string
    :initform "")
   (count
    :reader count
    :initarg :count
    :type cl:integer
    :initform 0))
)

(cl:defclass Chatter (<Chatter>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Chatter>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Chatter)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test_pub_sub_protobuf-msg:<Chatter> is deprecated: use test_pub_sub_protobuf-msg:Chatter instead.")))

(cl:ensure-generic-function 'message-val :lambda-list '(m))
(cl:defmethod message-val ((m <Chatter>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_pub_sub_protobuf-msg:message-val is deprecated.  Use test_pub_sub_protobuf-msg:message instead.")
  (message m))

(cl:ensure-generic-function 'count-val :lambda-list '(m))
(cl:defmethod count-val ((m <Chatter>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_pub_sub_protobuf-msg:count-val is deprecated.  Use test_pub_sub_protobuf-msg:count instead.")
  (count m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Chatter>) ostream)
  "Serializes a message object of type '<Chatter>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'message))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'message))
  (cl:let* ((signed (cl:slot-value msg 'count)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Chatter>) istream)
  "Deserializes a message object of type '<Chatter>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'message) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'message) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'count) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Chatter>)))
  "Returns string type for a message object of type '<Chatter>"
  "test_pub_sub_protobuf/Chatter")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Chatter)))
  "Returns string type for a message object of type 'Chatter"
  "test_pub_sub_protobuf/Chatter")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Chatter>)))
  "Returns md5sum for a message object of type '<Chatter>"
  "36d943046b5f520e12ac758c9f6277d7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Chatter)))
  "Returns md5sum for a message object of type 'Chatter"
  "36d943046b5f520e12ac758c9f6277d7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Chatter>)))
  "Returns full string definition for message of type '<Chatter>"
  (cl:format cl:nil "string message~%int32 count~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Chatter)))
  "Returns full string definition for message of type 'Chatter"
  (cl:format cl:nil "string message~%int32 count~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Chatter>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'message))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Chatter>))
  "Converts a ROS message object to a list"
  (cl:list 'Chatter
    (cl:cons ':message (message msg))
    (cl:cons ':count (count msg))
))
