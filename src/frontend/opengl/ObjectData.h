#ifndef OBJECT_DATA_H
#define OBJECT_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../backend/arrays.h"

struct FloatVec3 {
  float x;
  float y;
  float z;
};

typedef struct FloatVec3 FloatVec3;

struct ObjectData {
  FloatArray vertices;
  IntArray faces;

  int numberOfVertices;
  int numberOfFaces;

  FloatVec3 center;
};

typedef struct ObjectData ObjectData;

#ifdef __cplusplus
}
#endif

#endif
