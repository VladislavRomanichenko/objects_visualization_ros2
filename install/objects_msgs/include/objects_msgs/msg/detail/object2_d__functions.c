// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from objects_msgs:msg/Object2D.idl
// generated code does not contain a copyright notice
#include "objects_msgs/msg/detail/object2_d__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
objects_msgs__msg__Object2D__init(objects_msgs__msg__Object2D * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // label
  // score
  // x
  // y
  // width
  // height
  return true;
}

void
objects_msgs__msg__Object2D__fini(objects_msgs__msg__Object2D * msg)
{
  if (!msg) {
    return;
  }
  // id
  // label
  // score
  // x
  // y
  // width
  // height
}

bool
objects_msgs__msg__Object2D__are_equal(const objects_msgs__msg__Object2D * lhs, const objects_msgs__msg__Object2D * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // label
  if (lhs->label != rhs->label) {
    return false;
  }
  // score
  if (lhs->score != rhs->score) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // width
  if (lhs->width != rhs->width) {
    return false;
  }
  // height
  if (lhs->height != rhs->height) {
    return false;
  }
  return true;
}

bool
objects_msgs__msg__Object2D__copy(
  const objects_msgs__msg__Object2D * input,
  objects_msgs__msg__Object2D * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // label
  output->label = input->label;
  // score
  output->score = input->score;
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // width
  output->width = input->width;
  // height
  output->height = input->height;
  return true;
}

objects_msgs__msg__Object2D *
objects_msgs__msg__Object2D__create()
{
  objects_msgs__msg__Object2D * msg = (objects_msgs__msg__Object2D *)malloc(sizeof(objects_msgs__msg__Object2D));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(objects_msgs__msg__Object2D));
  bool success = objects_msgs__msg__Object2D__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
objects_msgs__msg__Object2D__destroy(objects_msgs__msg__Object2D * msg)
{
  if (msg) {
    objects_msgs__msg__Object2D__fini(msg);
  }
  free(msg);
}


bool
objects_msgs__msg__Object2D__Sequence__init(objects_msgs__msg__Object2D__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  objects_msgs__msg__Object2D * data = NULL;
  if (size) {
    data = (objects_msgs__msg__Object2D *)calloc(size, sizeof(objects_msgs__msg__Object2D));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = objects_msgs__msg__Object2D__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        objects_msgs__msg__Object2D__fini(&data[i - 1]);
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
objects_msgs__msg__Object2D__Sequence__fini(objects_msgs__msg__Object2D__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      objects_msgs__msg__Object2D__fini(&array->data[i]);
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

objects_msgs__msg__Object2D__Sequence *
objects_msgs__msg__Object2D__Sequence__create(size_t size)
{
  objects_msgs__msg__Object2D__Sequence * array = (objects_msgs__msg__Object2D__Sequence *)malloc(sizeof(objects_msgs__msg__Object2D__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = objects_msgs__msg__Object2D__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
objects_msgs__msg__Object2D__Sequence__destroy(objects_msgs__msg__Object2D__Sequence * array)
{
  if (array) {
    objects_msgs__msg__Object2D__Sequence__fini(array);
  }
  free(array);
}

bool
objects_msgs__msg__Object2D__Sequence__are_equal(const objects_msgs__msg__Object2D__Sequence * lhs, const objects_msgs__msg__Object2D__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!objects_msgs__msg__Object2D__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
objects_msgs__msg__Object2D__Sequence__copy(
  const objects_msgs__msg__Object2D__Sequence * input,
  objects_msgs__msg__Object2D__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(objects_msgs__msg__Object2D);
    objects_msgs__msg__Object2D * data =
      (objects_msgs__msg__Object2D *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!objects_msgs__msg__Object2D__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          objects_msgs__msg__Object2D__fini(&data[i]);
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
    if (!objects_msgs__msg__Object2D__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
