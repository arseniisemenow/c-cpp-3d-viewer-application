#ifndef MESH_DATA_H
#define MESH_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "arrays.h"

struct FloatVec3 {
  float x;
  float y;
  float z;
};

typedef struct FloatVec3 FloatVec3;

struct MeshData {
  FloatArray vertices;
  IntArray faces;

  int numberOfVertices;
  int numberOfEdges;

  FloatVec3 center;
};

typedef struct MeshData MeshData;

#ifdef __cplusplus
}
#endif

#endif
