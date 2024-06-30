// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from objects_msgs:msg/DynamicObjectArray.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT_ARRAY__TRAITS_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT_ARRAY__TRAITS_HPP_

#include "objects_msgs/msg/detail/dynamic_object_array__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'objects'
#include "objects_msgs/msg/detail/dynamic_object__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const objects_msgs::msg::DynamicObjectArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_yaml(msg.header, out, indentation + 2);
  }

  // member: objects
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.objects.size() == 0) {
      out << "objects: []\n";
    } else {
      out << "objects:\n";
      for (auto item : msg.objects) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const objects_msgs::msg::DynamicObjectArray & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<objects_msgs::msg::DynamicObjectArray>()
{
  return "objects_msgs::msg::DynamicObjectArray";
}

template<>
inline const char * name<objects_msgs::msg::DynamicObjectArray>()
{
  return "objects_msgs/msg/DynamicObjectArray";
}

template<>
struct has_fixed_size<objects_msgs::msg::DynamicObjectArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<objects_msgs::msg::DynamicObjectArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<objects_msgs::msg::DynamicObjectArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT_ARRAY__TRAITS_HPP_
