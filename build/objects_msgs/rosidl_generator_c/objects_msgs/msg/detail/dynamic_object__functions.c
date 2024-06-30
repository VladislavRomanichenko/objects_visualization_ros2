// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from objects_msgs:msg/DynamicObject.idl
// generated code does not contain a copyright notice
#include "objects_msgs/msg/detail/dynamic_object__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `object`
#include "objects_msgs/msg/detail/object__functions.h"
// Member `velocity`
#include "geometry_msgs/msg/detail/twist__functions.h"
// Member `prediction`
#include "geometry_msgs/msg/detail/pose_stamped__functions.h"
// Member `trajectory`
#include "geometry_msgs/msg/detail/point_stamped__functions.h"

bool
objects_msgs__msg__DynamicObject__init(objects_msgs__msg__DynamicObject * msg)
{
  if (!msg) {
    return false;
  }
  // object
  if (!objects_msgs__msg__Object__init(&msg->object)) {
    objects_msgs__msg__DynamicObject__fini(msg);
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Twist__init(&msg->velocity)) {
    objects_msgs__msg__DynamicObject__fini(msg);
    return false;
  }
  // prediction
  if (!geometry_msgs__msg__PoseStamped__Sequence__init(&msg->prediction, 0)) {
    objects_msgs__msg__DynamicObject__fini(msg);
    return false;
  }
  // trajectory
  if (!geometry_msgs__msg__PointStamped__Sequence__init(&msg->trajectory, 0)) {
    objects_msgs__msg__DynamicObject__fini(msg);
    return false;
  }
  return true;
}

void
objects_msgs__msg__DynamicObject__fini(objects_msgs__msg__DynamicObject * msg)
{
  if (!msg) {
    return;
  }
  // object
  objects_msgs__msg__Object__fini(&msg->object);
  // velocity
  geometry_msgs__msg__Twist__fini(&msg->velocity);
  // prediction
  geometry_msgs__msg__PoseStamped__Sequence__fini(&msg->prediction);
  // trajectory
  geometry_msgs__msg__PointStamped__Sequence__fini(&msg->trajectory);
}

bool
objects_msgs__msg__DynamicObject__are_equal(const objects_msgs__msg__DynamicObject * lhs, const objects_msgs__msg__DynamicObject * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // object
  if (!objects_msgs__msg__Object__are_equal(
      &(lhs->object), &(rhs->object)))
  {
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Twist__are_equal(
      &(lhs->velocity), &(rhs->velocity)))
  {
    return false;
  }
  // prediction
  if (!geometry_msgs__msg__PoseStamped__Sequence__are_equal(
      &(lhs->prediction), &(rhs->prediction)))
  {
    return false;
  }
  // trajectory
  if (!geometry_msgs__msg__PointStamped__Sequence__are_equal(
      &(lhs->trajectory), &(rhs->trajectory)))
  {
    return false;
  }
  return true;
}

bool
objects_msgs__msg__DynamicObject__copy(
  const objects_msgs__msg__DynamicObject * input,
  objects_msgs__msg__DynamicObject * output)
{
  if (!input || !output) {
    return false;
  }
  // object
  if (!objects_msgs__msg__Object__copy(
      &(input->object), &(output->object)))
  {
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Twist__copy(
      &(input->velocity), &(output->velocity)))
  {
    return false;
  }
  // prediction
  if (!geometry_msgs__msg__PoseStamped__Sequence__copy(
      &(input->prediction), &(output->prediction)))
  {
    return false;
  }
  // trajectory
  if (!geometry_msgs__msg__PointStamped__Sequence__copy(
      &(input->trajectory), &(output->trajectory)))
  {
    return false;
  }
  return true;
}

objects_msgs__msg__DynamicObject *
objects_msgs__msg__DynamicObject__create()
{
  objects_msgs__msg__DynamicObject * msg = (objects_msgs__msg__DynamicObject *)malloc(sizeof(objects_msgs__msg__DynamicObject));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(objects_msgs__msg__DynamicObject));
  bool success = objects_msgs__msg__DynamicObject__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
objects_msgs__msg__DynamicObject__destroy(objects_msgs__msg__DynamicObject * msg)
{
  if (msg) {
    objects_msgs__msg__DynamicObject__fini(msg);
  }
  free(msg);
}


bool
objects_msgs__msg__DynamicObject__Sequence__init(objects_msgs__msg__DynamicObject__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  objects_msgs__msg__DynamicObject * data = NULL;
  if (size) {
    data = (objects_msgs__msg__DynamicObject *)calloc(size, sizeof(objects_msgs__msg__DynamicObject));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = objects_msgs__msg__DynamicObject__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        objects_msgs__msg__DynamicObject__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
objects_msgs__msg__DynamicObject__Sequence__fini(objects_msgs__msg__DynamicObject__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      objects_msgs__msg__DynamicObject__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

objects_msgs__msg__DynamicObject__Sequence *
objects_msgs__msg__DynamicObject__Sequence__create(size_t size)
{
  objects_msgs__msg__DynamicObject__Sequence * array = (objects_msgs__msg__DynamicObject__Sequence *)malloc(sizeof(objects_msgs__msg__DynamicObject__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = objects_msgs__msg__DynamicObject__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
objects_msgs__msg__DynamicObject__Sequence__destroy(objects_msgs__msg__DynamicObject__Sequence * array)
{
  if (array) {
    objects_msgs__msg__DynamicObject__Sequence__fini(array);
  }
  free(array);
}

bool
objects_msgs__msg__DynamicObject__Sequence__are_equal(const objects_msgs__msg__DynamicObject__Sequence * lhs, const objects_msgs__msg__DynamicObject__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!objects_msgs__msg__DynamicObject__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
objects_msgs__msg__DynamicObject__Sequence__copy(
  const objects_msgs__msg__DynamicObject__Sequence * input,
  objects_msgs__msg__DynamicObject__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(objects_msgs__msg__DynamicObject);
    objects_msgs__msg__DynamicObject * data =
      (objects_msgs__msg__DynamicObject *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!objects_msgs__msg__DynamicObject__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          objects_msgs__msg__DynamicObject__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!objects_msgs__msg__DynamicObject__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
