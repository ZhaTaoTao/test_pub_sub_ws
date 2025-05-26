;; Auto-generated. Do not edit!


(when (boundp 'test_protobuf_msg::Chatter)
  (if (not (find-package "TEST_PROTOBUF_MSG"))
    (make-package "TEST_PROTOBUF_MSG"))
  (shadow 'Chatter (find-package "TEST_PROTOBUF_MSG")))
(unless (find-package "TEST_PROTOBUF_MSG::CHATTER")
  (make-package "TEST_PROTOBUF_MSG::CHATTER"))

(in-package "ROS")
;;//! \htmlinclude Chatter.msg.html


(defclass test_protobuf_msg::Chatter
  :super ros::object
  :slots (_message _count ))

(defmethod test_protobuf_msg::Chatter
  (:init
   (&key
    ((:message __message) "")
    ((:count __count) 0)
    )
   (send-super :init)
   (setq _message (string __message))
   (setq _count (round __count))
   self)
  (:message
   (&optional __message)
   (if __message (setq _message __message)) _message)
  (:count
   (&optional __count)
   (if __count (setq _count __count)) _count)
  (:serialization-length
   ()
   (+
    ;; string _message
    4 (length _message)
    ;; int32 _count
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _message
       (write-long (length _message) s) (princ _message s)
     ;; int32 _count
       (write-long _count s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _message
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _message (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int32 _count
     (setq _count (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get test_protobuf_msg::Chatter :md5sum-) "36d943046b5f520e12ac758c9f6277d7")
(setf (get test_protobuf_msg::Chatter :datatype-) "test_protobuf_msg/Chatter")
(setf (get test_protobuf_msg::Chatter :definition-)
      "string message 
int32 count
")



(provide :test_protobuf_msg/Chatter "36d943046b5f520e12ac758c9f6277d7")


