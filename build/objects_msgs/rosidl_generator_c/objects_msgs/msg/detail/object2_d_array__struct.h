// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from objects_msgs:msg/Object2DArray.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D_ARRAY__STRUCT_H_
#define OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'objects'
#include "objects_msgs/msg/detail/object2_d__struct.h"

// Struct defined in msg/Object2DArray in the package objects_msgs.
typedef struct objects_msgs__msg__Object2DArray
{
  std_msgs__msg__Header header;
  objects_msgs__msg__Object2D__Sequence objects;
} objects_msgs__msg__Object2DArray;

// Struct for a sequence of objects_msgs__msg__Object2DArray.
typedef struct objects_msgs__msg__Object2DArray__Sequence
{
  objects_msgs__msg__Object2DArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} objects_msgs__msg__Object2DArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D_ARRAY__STRUCT_H_
