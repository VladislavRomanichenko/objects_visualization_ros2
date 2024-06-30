// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from objects_msgs:msg/DynamicObject.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT__TRAITS_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT__TRAITS_HPP_

#include "objects_msgs/msg/detail/dynamic_object__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'object'
#include "objects_msgs/msg/detail/object__traits.hpp"
// Member 'velocity'
#include "geometry_msgs/msg/detail/twist__traits.hpp"
// Member 'prediction'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"
// Member 'trajectory'
#include "geometry_msgs/msg/detail/point_stamped__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const objects_msgs::msg::DynamicObject & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: object
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "object:\n";
    to_yaml(msg.object, out, indentation + 2);
  }

  // member: velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "velocity:\n";
    to_yaml(msg.velocity, out, indentation + 2);
  }

  // member: prediction
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.prediction.size() == 0) {
      out << "prediction: []\n";
    } else {
      out << "prediction:\n";
      for (auto item : msg.prediction) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: trajectory
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.trajectory.size() == 0) {
      out << "trajectory: []\n";
    } else {
      out << "trajectory:\n";
      for (auto item : msg.trajectory) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const objects_msgs::msg::DynamicObject & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<objects_msgs::msg::DynamicObject>()
{
  return "objects_msgs::msg::DynamicObject";
}

template<>
inline const char * name<objects_msgs::msg::DynamicObject>()
{
  return "objects_msgs/msg/DynamicObject";
}

template<>
struct has_fixed_size<objects_msgs::msg::DynamicObject>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<objects_msgs::msg::DynamicObject>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<objects_msgs::msg::DynamicObject>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT__TRAITS_HPP_
