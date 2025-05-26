
(cl:in-package :asdf)

(defsystem "test_pub_sub_protobuf-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Chatter" :depends-on ("_package_Chatter"))
    (:file "_package_Chatter" :depends-on ("_package"))
  ))