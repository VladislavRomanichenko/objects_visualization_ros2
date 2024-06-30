// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from objects_msgs:msg/DynamicObject.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT__BUILDER_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT__BUILDER_HPP_

#include "objects_msgs/msg/detail/dynamic_object__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace objects_msgs
{

namespace msg
{

namespace builder
{

class Init_DynamicObject_trajectory
{
public:
  explicit Init_DynamicObject_trajectory(::objects_msgs::msg::DynamicObject & msg)
  : msg_(msg)
  {}
  ::objects_msgs::msg::DynamicObject trajectory(::objects_msgs::msg::DynamicObject::_trajectory_type arg)
  {
    msg_.trajectory = std::move(arg);
    return std::move(msg_);
  }

private:
  ::objects_msgs::msg::DynamicObject msg_;
};

class Init_DynamicObject_prediction
{
public:
  explicit Init_DynamicObject_prediction(::objects_msgs::msg::DynamicObject & msg)
  : msg_(msg)
  {}
  Init_DynamicObject_trajectory prediction(::objects_msgs::msg::DynamicObject::_prediction_type arg)
  {
    msg_.prediction = std::move(arg);
    return Init_DynamicObject_trajectory(msg_);
  }

private:
  ::objects_msgs::msg::DynamicObject msg_;
};

class Init_DynamicObject_velocity
{
public:
  explicit Init_DynamicObject_velocity(::objects_msgs::msg::DynamicObject & msg)
  : msg_(msg)
  {}
  Init_DynamicObject_prediction velocity(::objects_msgs::msg::DynamicObject::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_DynamicObject_prediction(msg_);
  }

private:
  ::objects_msgs::msg::DynamicObject msg_;
};

class Init_DynamicObject_object
{
public:
  Init_DynamicObject_object()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DynamicObject_velocity object(::objects_msgs::msg::DynamicObject::_object_type arg)
  {
    msg_.object = std::move(arg);
    return Init_DynamicObject_velocity(msg_);
  }

private:
  ::objects_msgs::msg::DynamicObject msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::objects_msgs::msg::DynamicObject>()
{
  return objects_msgs::msg::builder::Init_DynamicObject_object();
}

}  // namespace objects_msgs

#endif  // OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT__BUILDER_HPP_
