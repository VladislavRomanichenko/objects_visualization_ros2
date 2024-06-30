// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from objects_msgs:msg/DynamicObjectArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "objects_msgs/msg/detail/dynamic_object_array__rosidl_typesupport_introspection_c.h"
#include "objects_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "objects_msgs/msg/detail/dynamic_object_array__functions.h"
#include "objects_msgs/msg/detail/dynamic_object_array__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `objects`
#include "objects_msgs/msg/dynamic_object.h"
// Member `objects`
#include "objects_msgs/msg/detail/dynamic_object__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  objects_msgs__msg__DynamicObjectArray__init(message_memory);
}

void DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_fini_function(void * message_memory)
{
  objects_msgs__msg__DynamicObjectArray__fini(message_memory);
}

size_t DynamicObjectArray__rosidl_typesupport_introspection_c__size_function__DynamicObject__objects(
  const void * untyped_member)
{
  const objects_msgs__msg__DynamicObject__Sequence * member =
    (const objects_msgs__msg__DynamicObject__Sequence *)(untyped_member);
  return member->size;
}

const void * DynamicObjectArray__rosidl_typesupport_introspection_c__get_const_function__DynamicObject__objects(
  const void * untyped_member, size_t index)
{
  const objects_msgs__msg__DynamicObject__Sequence * member =
    (const objects_msgs__msg__DynamicObject__Sequence *)(untyped_member);
  return &member->data[index];
}

void * DynamicObjectArray__rosidl_typesupport_introspection_c__get_function__DynamicObject__objects(
  void * untyped_member, size_t index)
{
  objects_msgs__msg__DynamicObject__Sequence * member =
    (objects_msgs__msg__DynamicObject__Sequence *)(untyped_member);
  return &member->data[index];
}

bool DynamicObjectArray__rosidl_typesupport_introspection_c__resize_function__DynamicObject__objects(
  void * untyped_member, size_t size)
{
  objects_msgs__msg__DynamicObject__Sequence * member =
    (objects_msgs__msg__DynamicObject__Sequence *)(untyped_member);
  objects_msgs__msg__DynamicObject__Sequence__fini(member);
  return objects_msgs__msg__DynamicObject__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(objects_msgs__msg__DynamicObjectArray, header),  // bytes offset in struct
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
    offsetof(objects_msgs__msg__DynamicObjectArray, objects),  // bytes offset in struct
    NULL,  // default value
    DynamicObjectArray__rosidl_typesupport_introspection_c__size_function__DynamicObject__objects,  // size() function pointer
    DynamicObjectArray__rosidl_typesupport_introspection_c__get_const_function__DynamicObject__objects,  // get_const(index) function pointer
    DynamicObjectArray__rosidl_typesupport_introspection_c__get_function__DynamicObject__objects,  // get(index) function pointer
    DynamicObjectArray__rosidl_typesupport_introspection_c__resize_function__DynamicObject__objects  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_message_members = {
  "objects_msgs__msg",  // message namespace
  "DynamicObjectArray",  // message name
  2,  // number of fields
  sizeof(objects_msgs__msg__DynamicObjectArray),
  DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_message_member_array,  // message members
  DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_init_function,  // function to initialize message memory (memory has to be allocated)
  DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_message_type_support_handle = {
  0,
  &DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_objects_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, objects_msgs, msg, DynamicObjectArray)() {
  DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, objects_msgs, msg, DynamicObject)();
  if (!DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_message_type_support_handle.typesupport_identifier) {
    DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &DynamicObjectArray__rosidl_typesupport_introspection_c__DynamicObjectArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
