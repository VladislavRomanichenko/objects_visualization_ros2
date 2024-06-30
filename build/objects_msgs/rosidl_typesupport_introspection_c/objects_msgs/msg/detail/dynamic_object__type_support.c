// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from objects_msgs:msg/DynamicObject.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "objects_msgs/msg/detail/dynamic_object__rosidl_typesupport_introspection_c.h"
#include "objects_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "objects_msgs/msg/detail/dynamic_object__functions.h"
#include "objects_msgs/msg/detail/dynamic_object__struct.h"


// Include directives for member types
// Member `object`
#include "objects_msgs/msg/object.h"
// Member `object`
#include "objects_msgs/msg/detail/object__rosidl_typesupport_introspection_c.h"
// Member `velocity`
#include "geometry_msgs/msg/twist.h"
// Member `velocity`
#include "geometry_msgs/msg/detail/twist__rosidl_typesupport_introspection_c.h"
// Member `prediction`
#include "geometry_msgs/msg/pose_stamped.h"
// Member `prediction`
#include "geometry_msgs/msg/detail/pose_stamped__rosidl_typesupport_introspection_c.h"
// Member `trajectory`
#include "geometry_msgs/msg/point_stamped.h"
// Member `trajectory`
#include "geometry_msgs/msg/detail/point_stamped__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  objects_msgs__msg__DynamicObject__init(message_memory);
}

void DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_fini_function(void * message_memory)
{
  objects_msgs__msg__DynamicObject__fini(message_memory);
}

size_t DynamicObject__rosidl_typesupport_introspection_c__size_function__PoseStamped__prediction(
  const void * untyped_member)
{
  const geometry_msgs__msg__PoseStamped__Sequence * member =
    (const geometry_msgs__msg__PoseStamped__Sequence *)(untyped_member);
  return member->size;
}

const void * DynamicObject__rosidl_typesupport_introspection_c__get_const_function__PoseStamped__prediction(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__PoseStamped__Sequence * member =
    (const geometry_msgs__msg__PoseStamped__Sequence *)(untyped_member);
  return &member->data[index];
}

void * DynamicObject__rosidl_typesupport_introspection_c__get_function__PoseStamped__prediction(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__PoseStamped__Sequence * member =
    (geometry_msgs__msg__PoseStamped__Sequence *)(untyped_member);
  return &member->data[index];
}

bool DynamicObject__rosidl_typesupport_introspection_c__resize_function__PoseStamped__prediction(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__PoseStamped__Sequence * member =
    (geometry_msgs__msg__PoseStamped__Sequence *)(untyped_member);
  geometry_msgs__msg__PoseStamped__Sequence__fini(member);
  return geometry_msgs__msg__PoseStamped__Sequence__init(member, size);
}

size_t DynamicObject__rosidl_typesupport_introspection_c__size_function__PointStamped__trajectory(
  const void * untyped_member)
{
  const geometry_msgs__msg__PointStamped__Sequence * member =
    (const geometry_msgs__msg__PointStamped__Sequence *)(untyped_member);
  return member->size;
}

const void * DynamicObject__rosidl_typesupport_introspection_c__get_const_function__PointStamped__trajectory(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__PointStamped__Sequence * member =
    (const geometry_msgs__msg__PointStamped__Sequence *)(untyped_member);
  return &member->data[index];
}

void * DynamicObject__rosidl_typesupport_introspection_c__get_function__PointStamped__trajectory(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__PointStamped__Sequence * member =
    (geometry_msgs__msg__PointStamped__Sequence *)(untyped_member);
  return &member->data[index];
}

bool DynamicObject__rosidl_typesupport_introspection_c__resize_function__PointStamped__trajectory(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__PointStamped__Sequence * member =
    (geometry_msgs__msg__PointStamped__Sequence *)(untyped_member);
  geometry_msgs__msg__PointStamped__Sequence__fini(member);
  return geometry_msgs__msg__PointStamped__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_message_member_array[4] = {
  {
    "object",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(objects_msgs__msg__DynamicObject, object),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "velocity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(objects_msgs__msg__DynamicObject, velocity),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "prediction",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(objects_msgs__msg__DynamicObject, prediction),  // bytes offset in struct
    NULL,  // default value
    DynamicObject__rosidl_typesupport_introspection_c__size_function__PoseStamped__prediction,  // size() function pointer
    DynamicObject__rosidl_typesupport_introspection_c__get_const_function__PoseStamped__prediction,  // get_const(index) function pointer
    DynamicObject__rosidl_typesupport_introspection_c__get_function__PoseStamped__prediction,  // get(index) function pointer
    DynamicObject__rosidl_typesupport_introspection_c__resize_function__PoseStamped__prediction  // resize(index) function pointer
  },
  {
    "trajectory",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(objects_msgs__msg__DynamicObject, trajectory),  // bytes offset in struct
    NULL,  // default value
    DynamicObject__rosidl_typesupport_introspection_c__size_function__PointStamped__trajectory,  // size() function pointer
    DynamicObject__rosidl_typesupport_introspection_c__get_const_function__PointStamped__trajectory,  // get_const(index) function pointer
    DynamicObject__rosidl_typesupport_introspection_c__get_function__PointStamped__trajectory,  // get(index) function pointer
    DynamicObject__rosidl_typesupport_introspection_c__resize_function__PointStamped__trajectory  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_message_members = {
  "objects_msgs__msg",  // message namespace
  "DynamicObject",  // message name
  4,  // number of fields
  sizeof(objects_msgs__msg__DynamicObject),
  DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_message_member_array,  // message members
  DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_init_function,  // function to initialize message memory (memory has to be allocated)
  DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_message_type_support_handle = {
  0,
  &DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_objects_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, objects_msgs, msg, DynamicObject)() {
  DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, objects_msgs, msg, Object)();
  DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Twist)();
  DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, PoseStamped)();
  DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, PointStamped)();
  if (!DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_message_type_support_handle.typesupport_identifier) {
    DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &DynamicObject__rosidl_typesupport_introspection_c__DynamicObject_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
