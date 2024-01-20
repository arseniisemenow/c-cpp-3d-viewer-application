#include "parser.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "../arrays.h"
#include "../constants.h"

ModelLoadingError readFloatFromLine(const char **line, float *number) {
  ModelLoadingError error = noModelLoadingError;
  char *endOfNumberPointer = NULL;
  *number = strtof(*line, &endOfNumberPointer);
  if (errno == ERANGE) {
    error = numberRangeError;
  } else if (*line == endOfNumberPointer) {
    error = insufficientVertexCoordinates;
  } else {
    *line = --endOfNumberPointer;
  }

  return error;
}

ModelLoadingError readIntFromLine(const char **line, long *number) {
  ModelLoadingError error = noModelLoadingError;
  char *endOfNumberPointer = NULL;
  errno = 0;
  *number = strtol(*line, &endOfNumberPointer, 10);
  if (errno == ERANGE) {
    error = numberRangeError;
  } else {
    *line = --endOfNumberPointer;
  }

  return error;
}

ModelLoadingError readAndAddVertexCoordinate(const char **line,
                                             FloatArray *vertices) {
  ModelLoadingError error = noModelLoadingError;
  float number = 0.0f;
  error = readFloatFromLine(line, &number);
  if (error == noModelLoadingError) {
    error = floatArrayAdd(vertices, number);
    ++(*line);
  }

  return error;
}

ModelLoadingError getVertexInfoFromLine(const char *line, MeshData *data) {
  line += 2;
  ModelLoadingError error = noModelLoadingError;

  for (int i = 0;
       i < constants.numberOfVertexCoordinates && error == noModelLoadingError;
       ++i) {
    error = readAndAddVertexCoordinate(&line, &data->vertices);
  }

  return error;
}

ModelLoadingError processEdgeIndex(int currentIndex, MeshData *data,
                                   bool *firstIndexWasSet,
                                   int *numberOfEdgeIndices, int *firstIndex) {
  ModelLoadingError error = noModelLoadingError;
  if (currentIndex > 0) {
    --currentIndex;
  } else if (currentIndex < 0) {
    currentIndex = data->numberOfVertices + currentIndex;
  }
  if (currentIndex >= data->numberOfVertices || currentIndex < 0) {
    error = indexOutOfBounds;
  }

  if (error == noModelLoadingError) {
    error = intArrayAdd(&data->faces, currentIndex);
    ++(*numberOfEdgeIndices);
  }
  if (*firstIndexWasSet && error == noModelLoadingError) {
    error = intArrayAdd(&data->faces, currentIndex);
    ++(*numberOfEdgeIndices);
  }

  if (!(*firstIndexWasSet)) {
    *firstIndex = currentIndex;
    *firstIndexWasSet = true;
  }

  return error;
}

void skipToNextIndex(const char **line) {
  char nextSymbol = *((*line) + 1);
  char currentSymbol = 0;
  if (nextSymbol == '/') {
    ++(*line);
    currentSymbol = **line;
    while (**line && currentSymbol != ' ' &&
           (currentSymbol == '/' || isdigit(currentSymbol) ||
            currentSymbol == '-')) {
      ++(*line);
      currentSymbol = **line;
    }
  }
  ++(*line);
  currentSymbol = **line;
  while (**line && !isdigit(currentSymbol) && currentSymbol != '-') {
    ++(*line);
    currentSymbol = **line;
  }
}

ModelLoadingError getSurfaceInfoFromLine(const char *line, MeshData *data) {
  ModelLoadingError error = noModelLoadingError;
  bool firstIndexWasSet = false;
  int firstIndex = 0;
  int numberOfEdgeIndices = 0;
  line += 2;
  while (*line && error == noModelLoadingError) {
    long currentIndex = 0;
    error = readIntFromLine(&line, &currentIndex);
    if (error == noModelLoadingError) {
      error = processEdgeIndex(currentIndex, data, &firstIndexWasSet,
                               &numberOfEdgeIndices, &firstIndex);
      skipToNextIndex(&line);
    }
  }

  if (numberOfEdgeIndices % 2 != 0 && error == noModelLoadingError) {
    error = intArrayAdd(&data->faces, firstIndex);
    ++numberOfEdgeIndices;
  }

  if (error == noModelLoadingError) {
    data->numberOfEdges += numberOfEdgeIndices / 2;
  }

  return error;
}

float floatMin(float first, float second) {
  return (first < second ? first : second);
}

float floatMax(float first, float second) {
  return (first < second ? second : first);
}

FloatVec3 calculateBoundingBoxCenter(float *vertices, int numberOfVertices) {
  FloatVec3 minCorner = {vertices[0], vertices[1], vertices[2]};
  FloatVec3 maxCorner = {vertices[0], vertices[1], vertices[2]};

  for (int i = 0; i < numberOfVertices;
       i += constants.numberOfVertexCoordinates) {
    minCorner.x = floatMin(minCorner.x, vertices[i]);
    minCorner.y = floatMin(minCorner.y, vertices[i + 1]);
    minCorner.z = floatMin(minCorner.z, vertices[i + 2]);

    maxCorner.x = floatMax(maxCorner.x, vertices[i]);
    maxCorner.y = floatMax(maxCorner.y, vertices[i + 1]);
    maxCorner.z = floatMax(maxCorner.z, vertices[i + 2]);
  }

  FloatVec3 center = {0};
  center.x = (minCorner.x + maxCorner.x) / 2.0f;
  center.y = (minCorner.y + maxCorner.y) / 2.0f;
  center.z = (minCorner.z + maxCorner.z) / 2.0f;
  return center;
}

void clearMeshData(MeshData *data) {
  floatArrayDestroy(&data->vertices);
  intArrayDestroy(&data->faces);
  data->numberOfVertices = 0;
  data->numberOfEdges = 0;
  data->center.x = 0.0f;
  data->center.y = 0.0f;
  data->center.z = 0.0f;
}

ModelLoadingError parseObjFile(const char *filename, MeshData *data) {
  ModelLoadingError error = noModelLoadingError;

  FILE *objFile = fopen(filename, "r");
  if (objFile == NULL) {
    fprintf(stderr, "couldn't open the obj file\n");
    error = fileNotFound;
    return error;
  }

  error =
      floatArrayInitialize(constants.initialVertexArraySize, &data->vertices);
  if (error == noModelLoadingError) {
    error = intArrayInitialize(constants.initialEdgeArraySize, &data->faces);
  }

  char line[256] = {0};

  while (fgets(line, sizeof(line), objFile) && error == noModelLoadingError) {
    if (line[0] == 'v' && line[1] == ' ') {
      error = getVertexInfoFromLine(line, data);
      ++data->numberOfVertices;
    } else if (line[0] == 'f' && line[1] == ' ') {
      error = getSurfaceInfoFromLine(line, data);
    }
  }

  if (error == noModelLoadingError) {
    data->center =
        calculateBoundingBoxCenter(data->vertices.data, data->numberOfVertices);
  }

  if (error != noModelLoadingError) {
    clearMeshData(data);
  }

  fclose(objFile);

  return error;
}
