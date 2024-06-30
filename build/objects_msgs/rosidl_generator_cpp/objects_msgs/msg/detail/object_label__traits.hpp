// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from objects_msgs:msg/ObjectLabel.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__OBJECT_LABEL__TRAITS_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__OBJECT_LABEL__TRAITS_HPP_

#include "objects_msgs/msg/detail/object_label__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

namespace rosidl_generator_traits
{

inline void to_yaml(
  const objects_msgs::msg::ObjectLabel & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const objects_msgs::msg::ObjectLabel & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<objects_msgs::msg::ObjectLabel>()
{
  return "objects_msgs::msg::ObjectLabel";
}

template<>
inline const char * name<objects_msgs::msg::ObjectLabel>()
{
  return "objects_msgs/msg/ObjectLabel";
}

template<>
struct has_fixed_size<objects_msgs::msg::ObjectLabel>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<objects_msgs::msg::ObjectLabel>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<objects_msgs::msg::ObjectLabel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // OBJECTS_MSGS__MSG__DETAIL__OBJECT_LABEL__TRAITS_HPP_
