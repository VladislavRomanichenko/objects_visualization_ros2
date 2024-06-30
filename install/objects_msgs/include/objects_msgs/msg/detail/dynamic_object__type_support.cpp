// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from objects_msgs:msg/DynamicObject.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "objects_msgs/msg/detail/dynamic_object__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace objects_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void DynamicObject_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) objects_msgs::msg::DynamicObject(_init);
}

void DynamicObject_fini_function(void * message_memory)
{
  auto typed_message = static_cast<objects_msgs::msg::DynamicObject *>(message_memory);
  typed_message->~DynamicObject();
}

size_t size_function__DynamicObject__prediction(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<geometry_msgs::msg::PoseStamped> *>(untyped_member);
  return member->size();
}

const void * get_const_function__DynamicObject__prediction(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<geometry_msgs::msg::PoseStamped> *>(untyped_member);
  return &member[index];
}

void * get_function__DynamicObject__prediction(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<geometry_msgs::msg::PoseStamped> *>(untyped_member);
  return &member[index];
}

void resize_function__DynamicObject__prediction(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<geometry_msgs::msg::PoseStamped> *>(untyped_member);
  member->resize(size);
}

size_t size_function__DynamicObject__trajectory(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<geometry_msgs::msg::PointStamped> *>(untyped_member);
  return member->size();
}

const void * get_const_function__DynamicObject__trajectory(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<geometry_msgs::msg::PointStamped> *>(untyped_member);
  return &member[index];
}

void * get_function__DynamicObject__trajectory(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<geometry_msgs::msg::PointStamped> *>(untyped_member);
  return &member[index];
}

void resize_function__DynamicObject__trajectory(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<geometry_msgs::msg::PointStamped> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember DynamicObject_message_member_array[4] = {
  {
    "object",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<objects_msgs::msg::Object>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(objects_msgs::msg::DynamicObject, object),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "velocity",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::Twist>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(objects_msgs::msg::DynamicObject, velocity),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "prediction",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::PoseStamped>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(objects_msgs::msg::DynamicObject, prediction),  // bytes offset in struct
    nullptr,  // default value
    size_function__DynamicObject__prediction,  // size() function pointer
    get_const_function__DynamicObject__prediction,  // get_const(index) function pointer
    get_function__DynamicObject__prediction,  // get(index) function pointer
    resize_function__DynamicObject__prediction  // resize(index) function pointer
  },
  {
    "trajectory",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::PointStamped>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(objects_msgs::msg::DynamicObject, trajectory),  // bytes offset in struct
    nullptr,  // default value
    size_function__DynamicObject__trajectory,  // size() function pointer
    get_const_function__DynamicObject__trajectory,  // get_const(index) function pointer
    get_function__DynamicObject__trajectory,  // get(index) function pointer
    resize_function__DynamicObject__trajectory  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers DynamicObject_message_members = {
  "objects_msgs::msg",  // message namespace
  "DynamicObject",  // message name
  4,  // number of fields
  sizeof(objects_msgs::msg::DynamicObject),
  DynamicObject_message_member_array,  // message members
  DynamicObject_init_function,  // function to initialize message memory (memory has to be allocated)
  DynamicObject_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t DynamicObject_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &DynamicObject_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace objects_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<objects_msgs::msg::DynamicObject>()
{
  return &::objects_msgs::msg::rosidl_typesupport_introspection_cpp::DynamicObject_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, objects_msgs, msg, DynamicObject)() {
  return &::objects_msgs::msg::rosidl_typesupport_introspection_cpp::DynamicObject_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
