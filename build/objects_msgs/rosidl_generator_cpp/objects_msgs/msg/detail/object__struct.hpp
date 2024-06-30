// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from objects_msgs:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__OBJECT__STRUCT_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__OBJECT__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.hpp"
// Member 'size'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__objects_msgs__msg__Object __attribute__((deprecated))
#else
# define DEPRECATED__objects_msgs__msg__Object __declspec(deprecated)
#endif

namespace objects_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Object_
{
  using Type = Object_<ContainerAllocator>;

  explicit Object_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_init),
    size(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0l;
      this->label = 0l;
      this->score = 0.0f;
    }
  }

  explicit Object_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_alloc, _init),
    size(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0l;
      this->label = 0l;
      this->score = 0.0f;
    }
  }

  // field types and members
  using _id_type =
    int32_t;
  _id_type id;
  using _label_type =
    int32_t;
  _label_type label;
  using _score_type =
    float;
  _score_type score;
  using _pose_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _pose_type pose;
  using _size_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _size_type size;

  // setters for named parameter idiom
  Type & set__id(
    const int32_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__label(
    const int32_t & _arg)
  {
    this->label = _arg;
    return *this;
  }
  Type & set__score(
    const float & _arg)
  {
    this->score = _arg;
    return *this;
  }
  Type & set__pose(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__size(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->size = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    objects_msgs::msg::Object_<ContainerAllocator> *;
  using ConstRawPtr =
    const objects_msgs::msg::Object_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<objects_msgs::msg::Object_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<objects_msgs::msg::Object_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      objects_msgs::msg::Object_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<objects_msgs::msg::Object_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      objects_msgs::msg::Object_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<objects_msgs::msg::Object_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<objects_msgs::msg::Object_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<objects_msgs::msg::Object_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__objects_msgs__msg__Object
    std::shared_ptr<objects_msgs::msg::Object_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__objects_msgs__msg__Object
    std::shared_ptr<objects_msgs::msg::Object_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Object_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->label != other.label) {
      return false;
    }
    if (this->score != other.score) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    if (this->size != other.size) {
      return false;
    }
    return true;
  }
  bool operator!=(const Object_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Object_

// alias to use template instance with default allocator
using Object =
  objects_msgs::msg::Object_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace objects_msgs

#endif  // OBJECTS_MSGS__MSG__DETAIL__OBJECT__STRUCT_HPP_
