// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from objects_msgs:msg/Object2DArray.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D_ARRAY__BUILDER_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D_ARRAY__BUILDER_HPP_

#include "objects_msgs/msg/detail/object2_d_array__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace objects_msgs
{

namespace msg
{

namespace builder
{

class Init_Object2DArray_objects
{
public:
  explicit Init_Object2DArray_objects(::objects_msgs::msg::Object2DArray & msg)
  : msg_(msg)
  {}
  ::objects_msgs::msg::Object2DArray objects(::objects_msgs::msg::Object2DArray::_objects_type arg)
  {
    msg_.objects = std::move(arg);
    return std::move(msg_);
  }

private:
  ::objects_msgs::msg::Object2DArray msg_;
};

class Init_Object2DArray_header
{
public:
  Init_Object2DArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Object2DArray_objects header(::objects_msgs::msg::Object2DArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Object2DArray_objects(msg_);
  }

private:
  ::objects_msgs::msg::Object2DArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::objects_msgs::msg::Object2DArray>()
{
  return objects_msgs::msg::builder::Init_Object2DArray_header();
}

}  // namespace objects_msgs

#endif  // OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D_ARRAY__BUILDER_HPP_
