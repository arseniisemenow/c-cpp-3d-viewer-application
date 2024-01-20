#include "affine_transformations.h"

#include <math.h>

#include "constants.h"

int get4x4MatrixIndex(int row, int column) { return (row * 4 + column); }

void modifyValuesForRotation(float *matrix, int firstRow, int secondRow,
                             int column, double sinTheta, double cosTheta) {
  float currentY = matrix[get4x4MatrixIndex(firstRow, column)];
  float currentZ = matrix[get4x4MatrixIndex(secondRow, column)];
  matrix[get4x4MatrixIndex(firstRow, column)] =
      currentY * cosTheta + currentZ * sinTheta;
  matrix[get4x4MatrixIndex(secondRow, column)] =
      currentZ * cosTheta - currentY * sinTheta;
}

void rotateEachColumn(float *matrix, int firstRow, int secondRow,
                      double sinTheta, double cosTheta) {
  for (int i = 0; i < 4; ++i) {
    modifyValuesForRotation(matrix, firstRow, secondRow, i, sinTheta, cosTheta);
  }
}

void rotateX(float *matrix, double sinTheta, double cosTheta) {
  rotateEachColumn(matrix, 1, 2, sinTheta, cosTheta);
}

void rotateY(float *matrix, double sinTheta, double cosTheta) {
  rotateEachColumn(matrix, 2, 0, sinTheta, cosTheta);
}

void rotateZ(float *matrix, double sinTheta, double cosTheta) {
  rotateEachColumn(matrix, 0, 1, sinTheta, cosTheta);
}

void rotate(float *matrix, double angle, double xAxis, double yAxis,
            double zAxis) {
  angle = angle * constants.pi / 180.0f;
  double sinTheta = sin(angle);
  double cosTheta = cos(angle);

  if (xAxis != 0.0) {
    if (xAxis < 0.0) {
      sinTheta = -sinTheta;
    }
    rotateX(matrix, sinTheta, cosTheta);
  }
  if (yAxis != 0.0) {
    if (yAxis < 0.0) {
      sinTheta = -sinTheta;
    }
    rotateY(matrix, sinTheta, cosTheta);
  }
  if (zAxis != 0.0) {
    if (zAxis < 0.0) {
      sinTheta = -sinTheta;
    }
    rotateZ(matrix, sinTheta, cosTheta);
  }
}

void translate(float *matrix, double xTranslate, double yTranslate,
               double zTranslate) {
  matrix[get4x4MatrixIndex(3, 0)] += xTranslate;
  matrix[get4x4MatrixIndex(3, 1)] += yTranslate;
  matrix[get4x4MatrixIndex(3, 2)] += zTranslate;
}

void scale(float *matrix, double xScale, double yScale, double zScale) {
  matrix[get4x4MatrixIndex(0, 0)] *= xScale;
  matrix[get4x4MatrixIndex(0, 1)] *= xScale;
  matrix[get4x4MatrixIndex(0, 2)] *= xScale;
  matrix[get4x4MatrixIndex(0, 3)] *= xScale;

  matrix[get4x4MatrixIndex(1, 0)] *= yScale;
  matrix[get4x4MatrixIndex(1, 1)] *= yScale;
  matrix[get4x4MatrixIndex(1, 2)] *= yScale;
  matrix[get4x4MatrixIndex(1, 3)] *= yScale;

  matrix[get4x4MatrixIndex(2, 0)] *= zScale;
  matrix[get4x4MatrixIndex(2, 1)] *= zScale;
  matrix[get4x4MatrixIndex(2, 2)] *= zScale;
  matrix[get4x4MatrixIndex(2, 3)] *= zScale;
}
