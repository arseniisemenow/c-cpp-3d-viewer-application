#include "arrays.h"

#include <stdlib.h>

ModelLoadingError floatArrayInitialize(int capacity, FloatArray *array) {
  ModelLoadingError error = noModelLoadingError;
  array->data = calloc(capacity, sizeof(float));
  if (array->data == NULL) {
    error = memoryAllocationError;
  } else {
    array->capacity = capacity;
    array->size = 0;
  }

  return error;
}

ModelLoadingError floatArrayAdd(FloatArray *array, float number) {
  ModelLoadingError error = noModelLoadingError;
  if (array->size == array->capacity) {
    array->capacity *= 2;
    void *reallocatedPointer =
        realloc(array->data, array->capacity * sizeof(float));
    if (reallocatedPointer == NULL) {
      error = memoryAllocationError;
    } else {
      array->data = reallocatedPointer;
    }
  }

  if (error == noModelLoadingError) {
    array->data[array->size++] = number;
  }

  return error;
}

void floatArrayDestroy(FloatArray *array) {
  free(array->data);
  array->data = NULL;
}

ModelLoadingError intArrayInitialize(int capacity, IntArray *array) {
  ModelLoadingError error = noModelLoadingError;
  array->data = calloc(capacity, sizeof(int));
  if (array->data == NULL) {
    error = memoryAllocationError;
  } else {
    array->capacity = capacity;
    array->size = 0;
  }

  return error;
}

ModelLoadingError intArrayAdd(IntArray *array, int number) {
  ModelLoadingError error = noModelLoadingError;
  if (array->size == array->capacity) {
    array->capacity *= 2;
    void *reallocatedPointer =
        realloc(array->data, array->capacity * sizeof(int));
    if (reallocatedPointer == NULL) {
      error = memoryAllocationError;
    } else {
      array->data = reallocatedPointer;
    }
  }

  if (error == noModelLoadingError) {
    array->data[array->size++] = number;
  }

  return error;
}

void intArrayDestroy(IntArray *array) {
  free(array->data);
  array->data = NULL;
}
