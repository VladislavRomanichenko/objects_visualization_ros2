// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from objects_msgs:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__OBJECT__TRAITS_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__OBJECT__TRAITS_HPP_

#include "objects_msgs/msg/detail/object__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__traits.hpp"
// Member 'size'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const objects_msgs::msg::Object & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: label
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "label: ";
    value_to_yaml(msg.label, out);
    out << "\n";
  }

  // member: score
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "score: ";
    value_to_yaml(msg.score, out);
    out << "\n";
  }

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_yaml(msg.pose, out, indentation + 2);
  }

  // member: size
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "size:\n";
    to_yaml(msg.size, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const objects_msgs::msg::Object & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<objects_msgs::msg::Object>()
{
  return "objects_msgs::msg::Object";
}

template<>
inline const char * name<objects_msgs::msg::Object>()
{
  return "objects_msgs/msg/Object";
}

template<>
struct has_fixed_size<objects_msgs::msg::Object>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Pose>::value && has_fixed_size<geometry_msgs::msg::Vector3>::value> {};

template<>
struct has_bounded_size<objects_msgs::msg::Object>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Pose>::value && has_bounded_size<geometry_msgs::msg::Vector3>::value> {};

template<>
struct is_message<objects_msgs::msg::Object>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // OBJECTS_MSGS__MSG__DETAIL__OBJECT__TRAITS_HPP_
