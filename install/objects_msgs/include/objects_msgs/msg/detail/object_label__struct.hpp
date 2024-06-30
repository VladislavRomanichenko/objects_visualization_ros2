// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from objects_msgs:msg/ObjectLabel.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__OBJECT_LABEL__STRUCT_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__OBJECT_LABEL__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__objects_msgs__msg__ObjectLabel __attribute__((deprecated))
#else
# define DEPRECATED__objects_msgs__msg__ObjectLabel __declspec(deprecated)
#endif

namespace objects_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ObjectLabel_
{
  using Type = ObjectLabel_<ContainerAllocator>;

  explicit ObjectLabel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit ObjectLabel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations
  static constexpr uint8_t VEHICLE =
    0u;
  static constexpr uint8_t PEDESTRIAN =
    1u;
  static constexpr uint8_t CYCLIST =
    2u;

  // pointer types
  using RawPtr =
    objects_msgs::msg::ObjectLabel_<ContainerAllocator> *;
  using ConstRawPtr =
    const objects_msgs::msg::ObjectLabel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<objects_msgs::msg::ObjectLabel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<objects_msgs::msg::ObjectLabel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      objects_msgs::msg::ObjectLabel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<objects_msgs::msg::ObjectLabel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      objects_msgs::msg::ObjectLabel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<objects_msgs::msg::ObjectLabel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<objects_msgs::msg::ObjectLabel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<objects_msgs::msg::ObjectLabel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__objects_msgs__msg__ObjectLabel
    std::shared_ptr<objects_msgs::msg::ObjectLabel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__objects_msgs__msg__ObjectLabel
    std::shared_ptr<objects_msgs::msg::ObjectLabel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ObjectLabel_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const ObjectLabel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ObjectLabel_

// alias to use template instance with default allocator
using ObjectLabel =
  objects_msgs::msg::ObjectLabel_<std::allocator<void>>;

// constant definitions
template<typename ContainerAllocator>
constexpr uint8_t ObjectLabel_<ContainerAllocator>::VEHICLE;
template<typename ContainerAllocator>
constexpr uint8_t ObjectLabel_<ContainerAllocator>::PEDESTRIAN;
template<typename ContainerAllocator>
constexpr uint8_t ObjectLabel_<ContainerAllocator>::CYCLIST;

}  // namespace msg

}  // namespace objects_msgs

#endif  // OBJECTS_MSGS__MSG__DETAIL__OBJECT_LABEL__STRUCT_HPP_
