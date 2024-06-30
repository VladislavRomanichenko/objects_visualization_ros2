// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from objects_msgs:msg/DynamicObjectArray.idl
// generated code does not contain a copyright notice

#ifndef OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT_ARRAY__FUNCTIONS_H_
#define OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT_ARRAY__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "objects_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "objects_msgs/msg/detail/dynamic_object_array__struct.h"

/// Initialize msg/DynamicObjectArray message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * objects_msgs__msg__DynamicObjectArray
 * )) before or use
 * objects_msgs__msg__DynamicObjectArray__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_objects_msgs
bool
objects_msgs__msg__DynamicObjectArray__init(objects_msgs__msg__DynamicObjectArray * msg);

/// Finalize msg/DynamicObjectArray message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_objects_msgs
void
objects_msgs__msg__DynamicObjectArray__fini(objects_msgs__msg__DynamicObjectArray * msg);

/// Create msg/DynamicObjectArray message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * objects_msgs__msg__DynamicObjectArray__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_objects_msgs
objects_msgs__msg__DynamicObjectArray *
objects_msgs__msg__DynamicObjectArray__create();

/// Destroy msg/DynamicObjectArray message.
/**
 * It calls
 * objects_msgs__msg__DynamicObjectArray__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_objects_msgs
void
objects_msgs__msg__DynamicObjectArray__destroy(objects_msgs__msg__DynamicObjectArray * msg);

/// Check for msg/DynamicObjectArray message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_objects_msgs
bool
objects_msgs__msg__DynamicObjectArray__are_equal(const objects_msgs__msg__DynamicObjectArray * lhs, const objects_msgs__msg__DynamicObjectArray * rhs);

/// Copy a msg/DynamicObjectArray message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_objects_msgs
bool
objects_msgs__msg__DynamicObjectArray__copy(
  const objects_msgs__msg__DynamicObjectArray * input,
  objects_msgs__msg__DynamicObjectArray * output);

/// Initialize array of msg/DynamicObjectArray messages.
/**
 * It allocates the memory for the number of elements and calls
 * objects_msgs__msg__DynamicObjectArray__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_objects_msgs
bool
objects_msgs__msg__DynamicObjectArray__Sequence__init(objects_msgs__msg__DynamicObjectArray__Sequence * array, size_t size);

/// Finalize array of msg/DynamicObjectArray messages.
/**
 * It calls
 * objects_msgs__msg__DynamicObjectArray__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_objects_msgs
void
objects_msgs__msg__DynamicObjectArray__Sequence__fini(objects_msgs__msg__DynamicObjectArray__Sequence * array);

/// Create array of msg/DynamicObjectArray messages.
/**
 * It allocates the memory for the array and calls
 * objects_msgs__msg__DynamicObjectArray__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_objects_msgs
objects_msgs__msg__DynamicObjectArray__Sequence *
objects_msgs__msg__DynamicObjectArray__Sequence__create(size_t size);

/// Destroy array of msg/DynamicObjectArray messages.
/**
 * It calls
 * objects_msgs__msg__DynamicObjectArray__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_objects_msgs
void
objects_msgs__msg__DynamicObjectArray__Sequence__destroy(objects_msgs__msg__DynamicObjectArray__Sequence * array);

/// Check for msg/DynamicObjectArray message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_objects_msgs
bool
objects_msgs__msg__DynamicObjectArray__Sequence__are_equal(const objects_msgs__msg__DynamicObjectArray__Sequence * lhs, const objects_msgs__msg__DynamicObjectArray__Sequence * rhs);

/// Copy an array of msg/DynamicObjectArray messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_objects_msgs
bool
objects_msgs__msg__DynamicObjectArray__Sequence__copy(
  const objects_msgs__msg__DynamicObjectArray__Sequence * input,
  objects_msgs__msg__DynamicObjectArray__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // OBJECTS_MSGS__MSG__DETAIL__DYNAMIC_OBJECT_ARRAY__FUNCTIONS_H_
