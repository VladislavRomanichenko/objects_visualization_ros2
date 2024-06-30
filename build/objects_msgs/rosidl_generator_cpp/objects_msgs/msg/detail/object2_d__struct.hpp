// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from objects_msgs:msg/Object2D.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D__STRUCT_HPP_
#define OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__objects_msgs__msg__Object2D __attribute__((deprecated))
#else
# define DEPRECATED__objects_msgs__msg__Object2D __declspec(deprecated)
#endif

namespace objects_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Object2D_
{
  using Type = Object2D_<ContainerAllocator>;

  explicit Object2D_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0l;
      this->label = 0l;
      this->score = 0.0f;
      this->x = 0l;
      this->y = 0l;
      this->width = 0l;
      this->height = 0l;
    }
  }

  explicit Object2D_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0l;
      this->label = 0l;
      this->score = 0.0f;
      this->x = 0l;
      this->y = 0l;
      this->width = 0l;
      this->height = 0l;
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
  using _x_type =
    int32_t;
  _x_type x;
  using _y_type =
    int32_t;
  _y_type y;
  using _width_type =
    int32_t;
  _width_type width;
  using _height_type =
    int32_t;
  _height_type height;

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
  Type & set__x(
    const int32_t & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const int32_t & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__width(
    const int32_t & _arg)
  {
    this->width = _arg;
    return *this;
  }
  Type & set__height(
    const int32_t & _arg)
  {
    this->height = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    objects_msgs::msg::Object2D_<ContainerAllocator> *;
  using ConstRawPtr =
    const objects_msgs::msg::Object2D_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<objects_msgs::msg::Object2D_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<objects_msgs::msg::Object2D_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      objects_msgs::msg::Object2D_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<objects_msgs::msg::Object2D_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      objects_msgs::msg::Object2D_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<objects_msgs::msg::Object2D_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<objects_msgs::msg::Object2D_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<objects_msgs::msg::Object2D_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__objects_msgs__msg__Object2D
    std::shared_ptr<objects_msgs::msg::Object2D_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__objects_msgs__msg__Object2D
    std::shared_ptr<objects_msgs::msg::Object2D_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Object2D_ & other) const
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
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->width != other.width) {
      return false;
    }
    if (this->height != other.height) {
      return false;
    }
    return true;
  }
  bool operator!=(const Object2D_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Object2D_

// alias to use template instance with default allocator
using Object2D =
  objects_msgs::msg::Object2D_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace objects_msgs

#endif  // OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D__STRUCT_HPP_
