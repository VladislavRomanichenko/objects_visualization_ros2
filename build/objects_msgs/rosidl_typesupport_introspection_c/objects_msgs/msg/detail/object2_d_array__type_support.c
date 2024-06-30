// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from objects_msgs:msg/Object2DArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "objects_msgs/msg/detail/object2_d_array__rosidl_typesupport_introspection_c.h"
#include "objects_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "objects_msgs/msg/detail/object2_d_array__functions.h"
#include "objects_msgs/msg/detail/object2_d_array__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `objects`
#include "objects_msgs/msg/object2_d.h"
// Member `objects`
#include "objects_msgs/msg/detail/object2_d__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  objects_msgs__msg__Object2DArray__init(message_memory);
}

void Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_fini_function(void * message_memory)
{
  objects_msgs__msg__Object2DArray__fini(message_memory);
}

size_t Object2DArray__rosidl_typesupport_introspection_c__size_function__Object2D__objects(
  const void * untyped_member)
{
  const objects_msgs__msg__Object2D__Sequence * member =
    (const objects_msgs__msg__Object2D__Sequence *)(untyped_member);
  return member->size;
}

const void * Object2DArray__rosidl_typesupport_introspection_c__get_const_function__Object2D__objects(
  const void * untyped_member, size_t index)
{
  const objects_msgs__msg__Object2D__Sequence * member =
    (const objects_msgs__msg__Object2D__Sequence *)(untyped_member);
  return &member->data[index];
}

void * Object2DArray__rosidl_typesupport_introspection_c__get_function__Object2D__objects(
  void * untyped_member, size_t index)
{
  objects_msgs__msg__Object2D__Sequence * member =
    (objects_msgs__msg__Object2D__Sequence *)(untyped_member);
  return &member->data[index];
}

bool Object2DArray__rosidl_typesupport_introspection_c__resize_function__Object2D__objects(
  void * untyped_member, size_t size)
{
  objects_msgs__msg__Object2D__Sequence * member =
    (objects_msgs__msg__Object2D__Sequence *)(untyped_member);
  objects_msgs__msg__Object2D__Sequence__fini(member);
  return objects_msgs__msg__Object2D__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(objects_msgs__msg__Object2DArray, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(objects_msgs__msg__Object2DArray, objects),  // bytes offset in struct
    NULL,  // default value
    Object2DArray__rosidl_typesupport_introspection_c__size_function__Object2D__objects,  // size() function pointer
    Object2DArray__rosidl_typesupport_introspection_c__get_const_function__Object2D__objects,  // get_const(index) function pointer
    Object2DArray__rosidl_typesupport_introspection_c__get_function__Object2D__objects,  // get(index) function pointer
    Object2DArray__rosidl_typesupport_introspection_c__resize_function__Object2D__objects  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_message_members = {
  "objects_msgs__msg",  // message namespace
  "Object2DArray",  // message name
  2,  // number of fields
  sizeof(objects_msgs__msg__Object2DArray),
  Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_message_member_array,  // message members
  Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_init_function,  // function to initialize message memory (memory has to be allocated)
  Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_message_type_support_handle = {
  0,
  &Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_objects_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, objects_msgs, msg, Object2DArray)() {
  Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, objects_msgs, msg, Object2D)();
  if (!Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_message_type_support_handle.typesupport_identifier) {
    Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &Object2DArray__rosidl_typesupport_introspection_c__Object2DArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
