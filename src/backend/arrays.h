#ifndef ARRAYS_H
#define ARRAYS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "error_enums.h"

struct FloatArray {
  float *data;
  int capacity;
  int size;
};

typedef struct FloatArray FloatArray;

ModelLoadingError floatArrayInitialize(int capacity, FloatArray *array);
ModelLoadingError floatArrayAdd(FloatArray *array, float number);
void floatArrayDestroy(FloatArray *array);

struct IntArray {
  int *data;
  int capacity;
  int size;
};

typedef struct IntArray IntArray;

ModelLoadingError intArrayInitialize(int capacity, IntArray *array);
ModelLoadingError intArrayAdd(IntArray *array, int number);
void intArrayDestroy(IntArray *array);

#ifdef __cplusplus
}
#endif

#endif
