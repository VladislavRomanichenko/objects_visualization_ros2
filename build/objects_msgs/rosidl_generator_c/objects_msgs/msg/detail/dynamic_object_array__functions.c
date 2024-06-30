// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from objects_msgs:msg/DynamicObjectArray.idl
// generated code does not contain a copyright notice
#include "objects_msgs/msg/detail/dynamic_object_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `objects`
#include "objects_msgs/msg/detail/dynamic_object__functions.h"

bool
objects_msgs__msg__DynamicObjectArray__init(objects_msgs__msg__DynamicObjectArray * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    objects_msgs__msg__DynamicObjectArray__fini(msg);
    return false;
  }
  // objects
  if (!objects_msgs__msg__DynamicObject__Sequence__init(&msg->objects, 0)) {
    objects_msgs__msg__DynamicObjectArray__fini(msg);
    return false;
  }
  return true;
}

void
objects_msgs__msg__DynamicObjectArray__fini(objects_msgs__msg__DynamicObjectArray * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // objects
  objects_msgs__msg__DynamicObject__Sequence__fini(&msg->objects);
}

bool
objects_msgs__msg__DynamicObjectArray__are_equal(const objects_msgs__msg__DynamicObjectArray * lhs, const objects_msgs__msg__DynamicObjectArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // objects
  if (!objects_msgs__msg__DynamicObject__Sequence__are_equal(
      &(lhs->objects), &(rhs->objects)))
  {
    return false;
  }
  return true;
}

bool
objects_msgs__msg__DynamicObjectArray__copy(
  const objects_msgs__msg__DynamicObjectArray * input,
  objects_msgs__msg__DynamicObjectArray * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // objects
  if (!objects_msgs__msg__DynamicObject__Sequence__copy(
      &(input->objects), &(output->objects)))
  {
    return false;
  }
  return true;
}

objects_msgs__msg__DynamicObjectArray *
objects_msgs__msg__DynamicObjectArray__create()
{
  objects_msgs__msg__DynamicObjectArray * msg = (objects_msgs__msg__DynamicObjectArray *)malloc(sizeof(objects_msgs__msg__DynamicObjectArray));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(objects_msgs__msg__DynamicObjectArray));
  bool success = objects_msgs__msg__DynamicObjectArray__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
objects_msgs__msg__DynamicObjectArray__destroy(objects_msgs__msg__DynamicObjectArray * msg)
{
  if (msg) {
    objects_msgs__msg__DynamicObjectArray__fini(msg);
  }
  free(msg);
}


bool
objects_msgs__msg__DynamicObjectArray__Sequence__init(objects_msgs__msg__DynamicObjectArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  objects_msgs__msg__DynamicObjectArray * data = NULL;
  if (size) {
    data = (objects_msgs__msg__DynamicObjectArray *)calloc(size, sizeof(objects_msgs__msg__DynamicObjectArray));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = objects_msgs__msg__DynamicObjectArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        objects_msgs__msg__DynamicObjectArray__fini(&data[i - 1]);
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
objects_msgs__msg__DynamicObjectArray__Sequence__fini(objects_msgs__msg__DynamicObjectArray__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      objects_msgs__msg__DynamicObjectArray__fini(&array->data[i]);
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

objects_msgs__msg__DynamicObjectArray__Sequence *
objects_msgs__msg__DynamicObjectArray__Sequence__create(size_t size)
{
  objects_msgs__msg__DynamicObjectArray__Sequence * array = (objects_msgs__msg__DynamicObjectArray__Sequence *)malloc(sizeof(objects_msgs__msg__DynamicObjectArray__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = objects_msgs__msg__DynamicObjectArray__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
objects_msgs__msg__DynamicObjectArray__Sequence__destroy(objects_msgs__msg__DynamicObjectArray__Sequence * array)
{
  if (array) {
    objects_msgs__msg__DynamicObjectArray__Sequence__fini(array);
  }
  free(array);
}

bool
objects_msgs__msg__DynamicObjectArray__Sequence__are_equal(const objects_msgs__msg__DynamicObjectArray__Sequence * lhs, const objects_msgs__msg__DynamicObjectArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!objects_msgs__msg__DynamicObjectArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
objects_msgs__msg__DynamicObjectArray__Sequence__copy(
  const objects_msgs__msg__DynamicObjectArray__Sequence * input,
  objects_msgs__msg__DynamicObjectArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(objects_msgs__msg__DynamicObjectArray);
    objects_msgs__msg__DynamicObjectArray * data =
      (objects_msgs__msg__DynamicObjectArray *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!objects_msgs__msg__DynamicObjectArray__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          objects_msgs__msg__DynamicObjectArray__fini(&data[i]);
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
    if (!objects_msgs__msg__DynamicObjectArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
