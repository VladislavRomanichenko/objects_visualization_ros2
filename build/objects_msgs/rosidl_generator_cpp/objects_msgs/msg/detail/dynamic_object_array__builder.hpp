// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from objects_msgs:msg/DynamicObjectArray.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT_ARRAY__BUILDER_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT_ARRAY__BUILDER_HPP_

#include "objects_msgs/msg/detail/dynamic_object_array__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace objects_msgs
{

namespace msg
{

namespace builder
{

class Init_DynamicObjectArray_objects
{
public:
  explicit Init_DynamicObjectArray_objects(::objects_msgs::msg::DynamicObjectArray & msg)
  : msg_(msg)
  {}
  ::objects_msgs::msg::DynamicObjectArray objects(::objects_msgs::msg::DynamicObjectArray::_objects_type arg)
  {
    msg_.objects = std::move(arg);
    return std::move(msg_);
  }

private:
  ::objects_msgs::msg::DynamicObjectArray msg_;
};

class Init_DynamicObjectArray_header
{
public:
  Init_DynamicObjectArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DynamicObjectArray_objects header(::objects_msgs::msg::DynamicObjectArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_DynamicObjectArray_objects(msg_);
  }

private:
  ::objects_msgs::msg::DynamicObjectArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::objects_msgs::msg::DynamicObjectArray>()
{
  return objects_msgs::msg::builder::Init_DynamicObjectArray_header();
}

}  // namespace objects_msgs

#endif  // OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT_ARRAY__BUILDER_HPP_
