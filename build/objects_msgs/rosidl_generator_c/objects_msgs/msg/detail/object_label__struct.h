// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from objects_msgs:msg/ObjectLabel.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__OBJECT_LABEL__STRUCT_H_
#define OBJECTS_MSGS__MSG__DETAIL__OBJECT_LABEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'VEHICLE'.
enum
{
  objects_msgs__msg__ObjectLabel__VEHICLE = 0
};

/// Constant 'PEDESTRIAN'.
enum
{
  objects_msgs__msg__ObjectLabel__PEDESTRIAN = 1
};

/// Constant 'CYCLIST'.
enum
{
  objects_msgs__msg__ObjectLabel__CYCLIST = 2
};

// Struct defined in msg/ObjectLabel in the package objects_msgs.
typedef struct objects_msgs__msg__ObjectLabel
{
  uint8_t structure_needs_at_least_one_member;
} objects_msgs__msg__ObjectLabel;

// Struct for a sequence of objects_msgs__msg__ObjectLabel.
typedef struct objects_msgs__msg__ObjectLabel__Sequence
{
  objects_msgs__msg__ObjectLabel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} objects_msgs__msg__ObjectLabel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OBJECTS_MSGS__MSG__DETAIL__OBJECT_LABEL__STRUCT_H_
