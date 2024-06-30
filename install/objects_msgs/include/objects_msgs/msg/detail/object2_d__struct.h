// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from objects_msgs:msg/Object2D.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D__STRUCT_H_
#define OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Object2D in the package objects_msgs.
typedef struct objects_msgs__msg__Object2D
{
  int32_t id;
  int32_t label;
  float score;
  int32_t x;
  int32_t y;
  int32_t width;
  int32_t height;
} objects_msgs__msg__Object2D;

// Struct for a sequence of objects_msgs__msg__Object2D.
typedef struct objects_msgs__msg__Object2D__Sequence
{
  objects_msgs__msg__Object2D * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} objects_msgs__msg__Object2D__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OBJECTS_MSGS__MSG__DETAIL__OBJECT2_D__STRUCT_H_
