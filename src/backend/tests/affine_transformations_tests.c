#include "affine_transformations_tests.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "../affine_transformations.h"

static const double kPrecision = 1e-6;

bool matricesAreEqual(const float *firstMatrix, const float *secondMatrix,
                      double tolerance) {
  for (int i = 0; i < 16; ++i) {
    if (fabs(firstMatrix[i] - secondMatrix[i]) > tolerance) {
      return false;
    }
  }

  return true;
}

START_TEST(translation_test_1) {
  float matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float desiredMatrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 3.0f, 4.0f, 1.0f};

  translate(matrix, 2.0, 3.0, 4.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Translation test 1 failed");
}
END_TEST

START_TEST(translation_test_2) {
  float matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float desiredMatrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f, 3.0f, 5.0f, 0.0f, 1.0f};

  translate(matrix, 3.0, 5.0, 0.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Translation test 2 failed");
}
END_TEST

START_TEST(translation_test_3) {
  float matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float desiredMatrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,   0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f, 3.0f, 5.0f, -50.0f, 1.0f};

  translate(matrix, 3.0, 5.0, -50.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Translation test 3 failed");
}
END_TEST

START_TEST(scaling_test_1) {
  float matrix[] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float desiredMatrix[] = {2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  scale(matrix, 2.0, 3.0, 4.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Scaling test 1 failed");
}
END_TEST

START_TEST(scaling_test_2) {
  float matrix[] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float desiredMatrix[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  scale(matrix, 0.0, 5.0, 6.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Scaling test 2 failed");
}
END_TEST

START_TEST(scaling_test_3) {
  float matrix[] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float desiredMatrix[] = {0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 5.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, -6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  scale(matrix, 0.0, 5.0, -6.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Scaling test 3 failed");
}
END_TEST

START_TEST(rotate_test_x_axis_90_degrees) {
  float matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float desiredMatrix[16] = {1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                             0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  rotate(matrix, 90.0, 1.0, 0.0, 0.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Rotate X-axis 90 degrees test failed");
}
END_TEST

START_TEST(rotate_test_y_axis_90_degrees) {
  float matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float desiredMatrix[16] = {0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                             1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  rotate(matrix, 90.0, 0.0, 1.0, 0.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Rotate Y-axis 90 degrees test failed");
}
END_TEST

START_TEST(rotate_test_z_axis_90_degrees) {
  float matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float desiredMatrix[16] = {0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f};

  rotate(matrix, 90.0, 0.0, 0.0, 1.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Rotate Z-axis 90 degrees test failed");
}
END_TEST

START_TEST(rotate_test_x_axis_45_degrees) {
  float matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float desiredMatrix[16] = {
      1.0f, 0.0f,       0.0f,      0.0f, 0.0f, 0.707107f, 0.707107f, 0.0f,
      0.0f, -0.707107f, 0.707107f, 0.0f, 0.0f, 0.0f,      0.0f,      1.0f};

  rotate(matrix, 45.0, 1.0, 0.0, 0.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Rotate X-axis 45 degrees test failed");
}
END_TEST

START_TEST(rotate_test_y_axis_60_degrees) {
  float matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float desiredMatrix[16] = {0.5f, 0.0f, -0.866025f, 0.0f, 0.0f, 1.0f,
                             0.0f, 0.0f, 0.866025f,  0.0f, 0.5f, 0.0f,
                             0.0f, 0.0f, 0.0f,       1.0f};

  rotate(matrix, 60.0, 0.0, 1.0, 0.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Rotate Y-axis 60 degrees test failed");
}
END_TEST

START_TEST(rotate_test_z_axis_random_angle) {
  float matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float angle = 37.5;

  float desiredMatrix[16] = {
      0.793353f, 0.608761f, 0.0f, 0.0f, -0.608761f, 0.793353f, 0.0f, 0.0f,
      0.0f,      0.0f,      1.0f, 0.0f, 0.0f,       0.0f,      0.0f, 1.0f};

  rotate(matrix, angle, 0.0, 0.0, 1.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Rotate Z-axis random angle test failed");
}
END_TEST

START_TEST(rotate_test_negative_x_axis_random_angle) {
  float matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float angle = 20.0;

  float desiredMatrix[16] = {
      1.0f, 0.0f,      0.0f,      0.0f, 0.0f, 0.939693f, -0.342020f, 0.0f,
      0.0f, 0.342020f, 0.939693f, 0.0f, 0.0f, 0.0f,      0.0f,       1.0f};

  rotate(matrix, angle, -1.0, 0.0, 0.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Rotate negative X-axis random angle test failed");
}
END_TEST

START_TEST(rotate_test_negative_y_axis_random_angle) {
  float matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float angle = 45.0;

  float desiredMatrix[16] = {0.707107f, 0.0f, 0.707107f,  0.0f, 0.0f,      1.0f,
                             0.0f,      0.0f, -0.707107f, 0.0f, 0.707107f, 0.0f,
                             0.0f,      0.0f, 0.0f,       1.0f};

  rotate(matrix, angle, 0.0, -1.0, 0.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Rotate negative Y-axis random angle test failed");
}
END_TEST

START_TEST(rotate_test_negative_z_axis_random_angle) {
  float matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float angle = 60.0;

  float desiredMatrix[16] = {0.5f, -0.866025f, 0.0f, 0.0f, 0.866025f, 0.5f,
                             0.0f, 0.0f,       0.0f, 0.0f, 1.0f,      0.0f,
                             0.0f, 0.0f,       0.0f, 1.0f};

  rotate(matrix, angle, 0.0, 0.0, -1.0);

  ck_assert_msg(matricesAreEqual(matrix, desiredMatrix, kPrecision),
                "Rotate negative Z-axis random angle test failed");
}
END_TEST

void applyAffineTransformationsSuite(Suite *mainSuite,
                                     TCase *mainTestCaseCore) {
  tcase_add_test(mainTestCaseCore, translation_test_1);
  tcase_add_test(mainTestCaseCore, translation_test_2);
  tcase_add_test(mainTestCaseCore, translation_test_3);
  tcase_add_test(mainTestCaseCore, scaling_test_1);
  tcase_add_test(mainTestCaseCore, scaling_test_2);
  tcase_add_test(mainTestCaseCore, scaling_test_3);
  tcase_add_test(mainTestCaseCore, rotate_test_x_axis_90_degrees);
  tcase_add_test(mainTestCaseCore, rotate_test_y_axis_90_degrees);
  tcase_add_test(mainTestCaseCore, rotate_test_z_axis_90_degrees);
  tcase_add_test(mainTestCaseCore, rotate_test_x_axis_45_degrees);
  tcase_add_test(mainTestCaseCore, rotate_test_y_axis_60_degrees);
  tcase_add_test(mainTestCaseCore, rotate_test_z_axis_random_angle);
  tcase_add_test(mainTestCaseCore, rotate_test_negative_x_axis_random_angle);
  tcase_add_test(mainTestCaseCore, rotate_test_negative_y_axis_random_angle);
  tcase_add_test(mainTestCaseCore, rotate_test_negative_z_axis_random_angle);

  suite_add_tcase(mainSuite, mainTestCaseCore);
}
