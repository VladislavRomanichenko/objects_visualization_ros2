// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from objects_msgs:msg/ObjectLabel.idl
// generated code does not contain a copyright notice
#include "objects_msgs/msg/detail/object_label__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
objects_msgs__msg__ObjectLabel__init(objects_msgs__msg__ObjectLabel * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
objects_msgs__msg__ObjectLabel__fini(objects_msgs__msg__ObjectLabel * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
objects_msgs__msg__ObjectLabel__are_equal(const objects_msgs__msg__ObjectLabel * lhs, const objects_msgs__msg__ObjectLabel * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
objects_msgs__msg__ObjectLabel__copy(
  const objects_msgs__msg__ObjectLabel * input,
  objects_msgs__msg__ObjectLabel * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

objects_msgs__msg__ObjectLabel *
objects_msgs__msg__ObjectLabel__create()
{
  objects_msgs__msg__ObjectLabel * msg = (objects_msgs__msg__ObjectLabel *)malloc(sizeof(objects_msgs__msg__ObjectLabel));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(objects_msgs__msg__ObjectLabel));
  bool success = objects_msgs__msg__ObjectLabel__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
objects_msgs__msg__ObjectLabel__destroy(objects_msgs__msg__ObjectLabel * msg)
{
  if (msg) {
    objects_msgs__msg__ObjectLabel__fini(msg);
  }
  free(msg);
}


bool
objects_msgs__msg__ObjectLabel__Sequence__init(objects_msgs__msg__ObjectLabel__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  objects_msgs__msg__ObjectLabel * data = NULL;
  if (size) {
    data = (objects_msgs__msg__ObjectLabel *)calloc(size, sizeof(objects_msgs__msg__ObjectLabel));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = objects_msgs__msg__ObjectLabel__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        objects_msgs__msg__ObjectLabel__fini(&data[i - 1]);
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
objects_msgs__msg__ObjectLabel__Sequence__fini(objects_msgs__msg__ObjectLabel__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      objects_msgs__msg__ObjectLabel__fini(&array->data[i]);
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

objects_msgs__msg__ObjectLabel__Sequence *
objects_msgs__msg__ObjectLabel__Sequence__create(size_t size)
{
  objects_msgs__msg__ObjectLabel__Sequence * array = (objects_msgs__msg__ObjectLabel__Sequence *)malloc(sizeof(objects_msgs__msg__ObjectLabel__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = objects_msgs__msg__ObjectLabel__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
objects_msgs__msg__ObjectLabel__Sequence__destroy(objects_msgs__msg__ObjectLabel__Sequence * array)
{
  if (array) {
    objects_msgs__msg__ObjectLabel__Sequence__fini(array);
  }
  free(array);
}

bool
objects_msgs__msg__ObjectLabel__Sequence__are_equal(const objects_msgs__msg__ObjectLabel__Sequence * lhs, const objects_msgs__msg__ObjectLabel__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!objects_msgs__msg__ObjectLabel__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
objects_msgs__msg__ObjectLabel__Sequence__copy(
  const objects_msgs__msg__ObjectLabel__Sequence * input,
  objects_msgs__msg__ObjectLabel__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(objects_msgs__msg__ObjectLabel);
    objects_msgs__msg__ObjectLabel * data =
      (objects_msgs__msg__ObjectLabel *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!objects_msgs__msg__ObjectLabel__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          objects_msgs__msg__ObjectLabel__fini(&data[i]);
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
    if (!objects_msgs__msg__ObjectLabel__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
