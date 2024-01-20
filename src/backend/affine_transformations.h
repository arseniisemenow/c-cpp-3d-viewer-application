#ifndef AFFINE_TRANSFORMATIONS_H
#define AFFINE_TRANSFORMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

void rotate(float *matrix, double angle, double xAxis, double yAxis,
            double zAxis);
void translate(float *matrix, double xTranslate, double yTranslate,
               double zTranslate);
void scale(float *matrix, double xScale, double yScale, double zScale);

#ifdef __cplusplus
}
#endif

#endif
