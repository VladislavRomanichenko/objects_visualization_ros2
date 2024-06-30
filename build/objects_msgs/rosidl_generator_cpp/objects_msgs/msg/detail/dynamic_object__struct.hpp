// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from objects_msgs:msg/DynamicObject.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT__STRUCT_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'object'
#include "objects_msgs/msg/detail/object__struct.hpp"
// Member 'velocity'
#include "geometry_msgs/msg/detail/twist__struct.hpp"
// Member 'prediction'
#include "geometry_msgs/msg/detail/pose_stamped__struct.hpp"
// Member 'trajectory'
#include "geometry_msgs/msg/detail/point_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__objects_msgs__msg__DynamicObject __attribute__((deprecated))
#else
# define DEPRECATED__objects_msgs__msg__DynamicObject __declspec(deprecated)
#endif

namespace objects_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DynamicObject_
{
  using Type = DynamicObject_<ContainerAllocator>;

  explicit DynamicObject_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : object(_init),
    velocity(_init)
  {
    (void)_init;
  }

  explicit DynamicObject_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : object(_alloc, _init),
    velocity(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _object_type =
    objects_msgs::msg::Object_<ContainerAllocator>;
  _object_type object;
  using _velocity_type =
    geometry_msgs::msg::Twist_<ContainerAllocator>;
  _velocity_type velocity;
  using _prediction_type =
    std::vector<geometry_msgs::msg::PoseStamped_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::PoseStamped_<ContainerAllocator>>>;
  _prediction_type prediction;
  using _trajectory_type =
    std::vector<geometry_msgs::msg::PointStamped_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::PointStamped_<ContainerAllocator>>>;
  _trajectory_type trajectory;

  // setters for named parameter idiom
  Type & set__object(
    const objects_msgs::msg::Object_<ContainerAllocator> & _arg)
  {
    this->object = _arg;
    return *this;
  }
  Type & set__velocity(
    const geometry_msgs::msg::Twist_<ContainerAllocator> & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__prediction(
    const std::vector<geometry_msgs::msg::PoseStamped_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::PoseStamped_<ContainerAllocator>>> & _arg)
  {
    this->prediction = _arg;
    return *this;
  }
  Type & set__trajectory(
    const std::vector<geometry_msgs::msg::PointStamped_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::PointStamped_<ContainerAllocator>>> & _arg)
  {
    this->trajectory = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    objects_msgs::msg::DynamicObject_<ContainerAllocator> *;
  using ConstRawPtr =
    const objects_msgs::msg::DynamicObject_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<objects_msgs::msg::DynamicObject_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<objects_msgs::msg::DynamicObject_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      objects_msgs::msg::DynamicObject_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<objects_msgs::msg::DynamicObject_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      objects_msgs::msg::DynamicObject_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<objects_msgs::msg::DynamicObject_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<objects_msgs::msg::DynamicObject_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<objects_msgs::msg::DynamicObject_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__objects_msgs__msg__DynamicObject
    std::shared_ptr<objects_msgs::msg::DynamicObject_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__objects_msgs__msg__DynamicObject
    std::shared_ptr<objects_msgs::msg::DynamicObject_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DynamicObject_ & other) const
  {
    if (this->object != other.object) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->prediction != other.prediction) {
      return false;
    }
    if (this->trajectory != other.trajectory) {
      return false;
    }
    return true;
  }
  bool operator!=(const DynamicObject_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DynamicObject_

// alias to use template instance with default allocator
using DynamicObject =
  objects_msgs::msg::DynamicObject_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace objects_msgs

#endif  // OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT__STRUCT_HPP_
