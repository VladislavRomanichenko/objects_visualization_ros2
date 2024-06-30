// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from objects_msgs:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__OBJECT__BUILDER_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__OBJECT__BUILDER_HPP_

#include "objects_msgs/msg/detail/object__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace objects_msgs
{

namespace msg
{

namespace builder
{

class Init_Object_size
{
public:
  explicit Init_Object_size(::objects_msgs::msg::Object & msg)
  : msg_(msg)
  {}
  ::objects_msgs::msg::Object size(::objects_msgs::msg::Object::_size_type arg)
  {
    msg_.size = std::move(arg);
    return std::move(msg_);
  }

private:
  ::objects_msgs::msg::Object msg_;
};

class Init_Object_pose
{
public:
  explicit Init_Object_pose(::objects_msgs::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_size pose(::objects_msgs::msg::Object::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_Object_size(msg_);
  }

private:
  ::objects_msgs::msg::Object msg_;
};

class Init_Object_score
{
public:
  explicit Init_Object_score(::objects_msgs::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_pose score(::objects_msgs::msg::Object::_score_type arg)
  {
    msg_.score = std::move(arg);
    return Init_Object_pose(msg_);
  }

private:
  ::objects_msgs::msg::Object msg_;
};

class Init_Object_label
{
public:
  explicit Init_Object_label(::objects_msgs::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_score label(::objects_msgs::msg::Object::_label_type arg)
  {
    msg_.label = std::move(arg);
    return Init_Object_score(msg_);
  }

private:
  ::objects_msgs::msg::Object msg_;
};

class Init_Object_id
{
public:
  Init_Object_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Object_label id(::objects_msgs::msg::Object::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_Object_label(msg_);
  }

private:
  ::objects_msgs::msg::Object msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::objects_msgs::msg::Object>()
{
  return objects_msgs::msg::builder::Init_Object_id();
}

}  // namespace objects_msgs

#endif  // OBJECTS_MSGS__MSG__DETAIL__OBJECT__BUILDER_HPP_
