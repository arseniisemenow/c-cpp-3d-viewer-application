#ifndef ERROR_ENUMS_H
#define ERROR_ENUMS_H

enum ModelLoadingError {
  noModelLoadingError,
  numberRangeError,
  insufficientVertexCoordinates,
  fileNotFound,
  memoryAllocationError,
  indexOutOfBounds,
};

typedef enum ModelLoadingError ModelLoadingError;

#endif
