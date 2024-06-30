// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from objects_msgs:msg/Object2D.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D__BUILDER_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D__BUILDER_HPP_

#include "objects_msgs/msg/detail/object2_d__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace objects_msgs
{

namespace msg
{

namespace builder
{

class Init_Object2D_height
{
public:
  explicit Init_Object2D_height(::objects_msgs::msg::Object2D & msg)
  : msg_(msg)
  {}
  ::objects_msgs::msg::Object2D height(::objects_msgs::msg::Object2D::_height_type arg)
  {
    msg_.height = std::move(arg);
    return std::move(msg_);
  }

private:
  ::objects_msgs::msg::Object2D msg_;
};

class Init_Object2D_width
{
public:
  explicit Init_Object2D_width(::objects_msgs::msg::Object2D & msg)
  : msg_(msg)
  {}
  Init_Object2D_height width(::objects_msgs::msg::Object2D::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_Object2D_height(msg_);
  }

private:
  ::objects_msgs::msg::Object2D msg_;
};

class Init_Object2D_y
{
public:
  explicit Init_Object2D_y(::objects_msgs::msg::Object2D & msg)
  : msg_(msg)
  {}
  Init_Object2D_width y(::objects_msgs::msg::Object2D::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Object2D_width(msg_);
  }

private:
  ::objects_msgs::msg::Object2D msg_;
};

class Init_Object2D_x
{
public:
  explicit Init_Object2D_x(::objects_msgs::msg::Object2D & msg)
  : msg_(msg)
  {}
  Init_Object2D_y x(::objects_msgs::msg::Object2D::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Object2D_y(msg_);
  }

private:
  ::objects_msgs::msg::Object2D msg_;
};

class Init_Object2D_score
{
public:
  explicit Init_Object2D_score(::objects_msgs::msg::Object2D & msg)
  : msg_(msg)
  {}
  Init_Object2D_x score(::objects_msgs::msg::Object2D::_score_type arg)
  {
    msg_.score = std::move(arg);
    return Init_Object2D_x(msg_);
  }

private:
  ::objects_msgs::msg::Object2D msg_;
};

class Init_Object2D_label
{
public:
  explicit Init_Object2D_label(::objects_msgs::msg::Object2D & msg)
  : msg_(msg)
  {}
  Init_Object2D_score label(::objects_msgs::msg::Object2D::_label_type arg)
  {
    msg_.label = std::move(arg);
    return Init_Object2D_score(msg_);
  }

private:
  ::objects_msgs::msg::Object2D msg_;
};

class Init_Object2D_id
{
public:
  Init_Object2D_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Object2D_label id(::objects_msgs::msg::Object2D::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_Object2D_label(msg_);
  }

private:
  ::objects_msgs::msg::Object2D msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::objects_msgs::msg::Object2D>()
{
  return objects_msgs::msg::builder::Init_Object2D_id();
}

}  // namespace objects_msgs

#endif  // OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D__BUILDER_HPP_
