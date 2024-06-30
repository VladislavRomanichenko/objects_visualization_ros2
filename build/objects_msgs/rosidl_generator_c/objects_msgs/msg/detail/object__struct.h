// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from objects_msgs:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__OBJECT__STRUCT_H_
#define OBJECTS_MSGS__MSG__DETAIL__OBJECT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.h"
// Member 'size'
#include "geometry_msgs/msg/detail/vector3__struct.h"

// Struct defined in msg/Object in the package objects_msgs.
typedef struct objects_msgs__msg__Object
{
  int32_t id;
  int32_t label;
  float score;
  geometry_msgs__msg__Pose pose;
  geometry_msgs__msg__Vector3 size;
} objects_msgs__msg__Object;

// Struct for a sequence of objects_msgs__msg__Object.
typedef struct objects_msgs__msg__Object__Sequence
{
  objects_msgs__msg__Object * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} objects_msgs__msg__Object__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OBJECTS_MSGS__MSG__DETAIL__OBJECT__STRUCT_H_
