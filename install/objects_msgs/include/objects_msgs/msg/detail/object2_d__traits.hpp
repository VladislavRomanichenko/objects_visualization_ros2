// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from objects_msgs:msg/Object2D.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D__TRAITS_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D__TRAITS_HPP_

#include "objects_msgs/msg/detail/object2_d__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

namespace rosidl_generator_traits
{

inline void to_yaml(
  const objects_msgs::msg::Object2D & msg,
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

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "width: ";
    value_to_yaml(msg.width, out);
    out << "\n";
  }

  // member: height
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "height: ";
    value_to_yaml(msg.height, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const objects_msgs::msg::Object2D & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<objects_msgs::msg::Object2D>()
{
  return "objects_msgs::msg::Object2D";
}

template<>
inline const char * name<objects_msgs::msg::Object2D>()
{
  return "objects_msgs/msg/Object2D";
}

template<>
struct has_fixed_size<objects_msgs::msg::Object2D>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<objects_msgs::msg::Object2D>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<objects_msgs::msg::Object2D>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D__TRAITS_HPP_
