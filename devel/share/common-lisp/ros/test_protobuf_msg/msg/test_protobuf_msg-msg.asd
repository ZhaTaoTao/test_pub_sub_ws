
(cl:in-package :asdf)

(defsystem "test_protobuf_msg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Chatter" :depends-on ("_package_Chatter"))
    (:file "_package_Chatter" :depends-on ("_package"))
  ))