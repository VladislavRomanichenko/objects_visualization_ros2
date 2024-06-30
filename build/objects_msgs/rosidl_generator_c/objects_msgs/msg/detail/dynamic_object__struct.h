// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from objects_msgs:msg/DynamicObject.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT__STRUCT_H_
#define OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'object'
#include "objects_msgs/msg/detail/object__struct.h"
// Member 'velocity'
#include "geometry_msgs/msg/detail/twist__struct.h"
// Member 'prediction'
#include "geometry_msgs/msg/detail/pose_stamped__struct.h"
// Member 'trajectory'
#include "geometry_msgs/msg/detail/point_stamped__struct.h"

// Struct defined in msg/DynamicObject in the package objects_msgs.
typedef struct objects_msgs__msg__DynamicObject
{
  objects_msgs__msg__Object object;
  geometry_msgs__msg__Twist velocity;
  geometry_msgs__msg__PoseStamped__Sequence prediction;
  geometry_msgs__msg__PointStamped__Sequence trajectory;
} objects_msgs__msg__DynamicObject;

// Struct for a sequence of objects_msgs__msg__DynamicObject.
typedef struct objects_msgs__msg__DynamicObject__Sequence
{
  objects_msgs__msg__DynamicObject * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} objects_msgs__msg__DynamicObject__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT__STRUCT_H_
