#include "affine_transformations_tests.h"
#include "model_loading_tests.h"

Suite *viewerSuite(void) {
  Suite *suite = NULL;
  TCase *testCaseCore = NULL;

  suite = suite_create("viewer");
  testCaseCore = tcase_create("Core");

  applyAffineTransformationsSuite(suite, testCaseCore);
  applyModelLoadingSuite(suite, testCaseCore);

  suite_add_tcase(suite, testCaseCore);

  return suite;
}

int main(void) {
  Suite *suite = NULL;
  SRunner *suiteRunner = NULL;

  suite = viewerSuite();
  suiteRunner = srunner_create(suite);

  srunner_run_all(suiteRunner, CK_NORMAL);
  srunner_ntests_failed(suiteRunner);
  srunner_free(suiteRunner);

  return 0;
}
