#include "model_loading_tests.h"

#include <stdio.h>
#include <stdlib.h>

#include "../parser/parser.h"

START_TEST(model_loading_test_normal_cube) {
  MeshData data = {0};
  ModelLoadingError myReturnValue = parseObjFile("obj_files/cube.obj", &data);
  int myNumberOfVertices = data.numberOfVertices;
  int myNumberOfEdges = data.numberOfEdges;

  int desiredNumberOfVertices = 8;
  int desiredNumberOfEdges = 36;
  ModelLoadingError desiredReturnValue = noModelLoadingError;

  ck_assert_int_eq(desiredReturnValue, myReturnValue);
  ck_assert_int_eq(desiredNumberOfVertices, myNumberOfVertices);
  ck_assert_int_eq(desiredNumberOfEdges, myNumberOfEdges);

  floatArrayDestroy(&data.vertices);
  intArrayDestroy(&data.faces);
}
END_TEST

START_TEST(model_loading_test_normal_lamp) {
  MeshData data = {0};
  ModelLoadingError myReturnValue = parseObjFile("obj_files/lamp.obj", &data);
  int myNumberOfVertices = data.numberOfVertices;
  int myNumberOfEdges = data.numberOfEdges;

  int desiredNumberOfVertices = 4440;
  int desiredNumberOfEdges = 17631;
  ModelLoadingError desiredReturnValue = noModelLoadingError;

  ck_assert_int_eq(desiredReturnValue, myReturnValue);
  ck_assert_int_eq(desiredNumberOfVertices, myNumberOfVertices);
  ck_assert_int_eq(desiredNumberOfEdges, myNumberOfEdges);

  floatArrayDestroy(&data.vertices);
  intArrayDestroy(&data.faces);
}
END_TEST

START_TEST(model_loading_test_normal_skull) {
  MeshData data = {0};
  ModelLoadingError myReturnValue = parseObjFile("obj_files/skull.obj", &data);
  int myNumberOfVertices = data.numberOfVertices;
  int myNumberOfEdges = data.numberOfEdges;

  int desiredNumberOfVertices = 6122;
  int desiredNumberOfEdges = 28611;
  ModelLoadingError desiredReturnValue = noModelLoadingError;

  ck_assert_int_eq(desiredReturnValue, myReturnValue);
  ck_assert_int_eq(desiredNumberOfVertices, myNumberOfVertices);
  ck_assert_int_eq(desiredNumberOfEdges, myNumberOfEdges);

  floatArrayDestroy(&data.vertices);
  intArrayDestroy(&data.faces);
}
END_TEST

START_TEST(model_loading_test_normal_earth) {
  MeshData data = {0};
  ModelLoadingError myReturnValue = parseObjFile("obj_files/Earth.obj", &data);
  int myNumberOfVertices = data.numberOfVertices;
  int myNumberOfEdges = data.numberOfEdges;

  int desiredNumberOfVertices = 1158;
  int desiredNumberOfEdges = 4608;
  ModelLoadingError desiredReturnValue = noModelLoadingError;

  ck_assert_int_eq(desiredReturnValue, myReturnValue);
  ck_assert_int_eq(desiredNumberOfVertices, myNumberOfVertices);
  ck_assert_int_eq(desiredNumberOfEdges, myNumberOfEdges);

  floatArrayDestroy(&data.vertices);
  intArrayDestroy(&data.faces);
}
END_TEST

START_TEST(model_loading_test_no_file) {
  MeshData data = {0};
  ModelLoadingError myReturnValue =
      parseObjFile("obj_files/no_file.obj", &data);
  int myNumberOfVertices = data.numberOfVertices;
  int myNumberOfEdges = data.numberOfEdges;

  int desiredNumberOfVertices = 0;
  int desiredNumberOfEdges = 0;
  ModelLoadingError desiredReturnValue = fileNotFound;

  ck_assert_int_eq(desiredReturnValue, myReturnValue);
  ck_assert_int_eq(desiredNumberOfVertices, myNumberOfVertices);
  ck_assert_int_eq(desiredNumberOfEdges, myNumberOfEdges);

  floatArrayDestroy(&data.vertices);
  intArrayDestroy(&data.faces);
}
END_TEST

START_TEST(model_loading_test_insufficient_vertex_coordinates) {
  MeshData data = {0};
  ModelLoadingError myReturnValue =
      parseObjFile("obj_files/two_coordinates.obj", &data);
  int myNumberOfVertices = data.numberOfVertices;
  int myNumberOfEdges = data.numberOfEdges;

  int desiredNumberOfVertices = 0;
  int desiredNumberOfEdges = 0;
  ModelLoadingError desiredReturnValue = insufficientVertexCoordinates;

  ck_assert_int_eq(desiredReturnValue, myReturnValue);
  ck_assert_int_eq(desiredNumberOfVertices, myNumberOfVertices);
  ck_assert_int_eq(desiredNumberOfEdges, myNumberOfEdges);

  floatArrayDestroy(&data.vertices);
  intArrayDestroy(&data.faces);
}
END_TEST

START_TEST(model_loading_test_number_out_of_range) {
  MeshData data = {0};
  ModelLoadingError myReturnValue =
      parseObjFile("obj_files/number_range_error.obj", &data);
  int myNumberOfVertices = data.numberOfVertices;
  int myNumberOfEdges = data.numberOfEdges;

  int desiredNumberOfVertices = 0;
  int desiredNumberOfEdges = 0;
  ModelLoadingError desiredReturnValue = numberRangeError;

  ck_assert_int_eq(desiredReturnValue, myReturnValue);
  ck_assert_int_eq(desiredNumberOfVertices, myNumberOfVertices);
  ck_assert_int_eq(desiredNumberOfEdges, myNumberOfEdges);

  floatArrayDestroy(&data.vertices);
  intArrayDestroy(&data.faces);
}
END_TEST

START_TEST(model_loading_test_index_out_of_bounds) {
  MeshData data = {0};
  ModelLoadingError myReturnValue =
      parseObjFile("obj_files/index_out_of_bounds.obj", &data);
  int myNumberOfVertices = data.numberOfVertices;
  int myNumberOfEdges = data.numberOfEdges;

  int desiredNumberOfVertices = 0;
  int desiredNumberOfEdges = 0;
  ModelLoadingError desiredReturnValue = indexOutOfBounds;

  ck_assert_int_eq(desiredReturnValue, myReturnValue);
  ck_assert_int_eq(desiredNumberOfVertices, myNumberOfVertices);
  ck_assert_int_eq(desiredNumberOfEdges, myNumberOfEdges);

  floatArrayDestroy(&data.vertices);
  intArrayDestroy(&data.faces);
}
END_TEST

void applyModelLoadingSuite(Suite *mainSuite, TCase *mainTestCaseCore) {
  tcase_add_test(mainTestCaseCore, model_loading_test_normal_cube);
  tcase_add_test(mainTestCaseCore, model_loading_test_normal_lamp);
  tcase_add_test(mainTestCaseCore, model_loading_test_normal_skull);
  tcase_add_test(mainTestCaseCore, model_loading_test_normal_earth);
  tcase_add_test(mainTestCaseCore, model_loading_test_no_file);
  tcase_add_test(mainTestCaseCore,
                 model_loading_test_insufficient_vertex_coordinates);
  tcase_add_test(mainTestCaseCore, model_loading_test_number_out_of_range);
  tcase_add_test(mainTestCaseCore, model_loading_test_index_out_of_bounds);

  suite_add_tcase(mainSuite, mainTestCaseCore);
}
