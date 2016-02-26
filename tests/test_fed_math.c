#include "minunit.h"

#include <stdlib.h>
#include <stdio.h>
#include <fed_math.h>

int tests_run = 0;

static char* test_multiplymat4() {
  return NULL;
}

static char* test_mulmatvec4() {
  return NULL;
}

static char* test_normalizevec4() {
  return NULL;
}

static char* test_dotvec4() {
  return NULL;
}

static char* test_crossvec4() {
  return NULL;
}

static char* test_rotateX() {
  return NULL;
}

static char* test_rotateY() {
  return NULL;
}

static char* test_rotateZ() {
  return NULL;
}

static char* test_scale() {
  return NULL;
}

static char* test_translate() {
  return NULL;
}

static char* test_perspective() {
  return NULL;
}

static char* test_orthogonal() {
  return NULL;
}

static char* test_lookAt() {
  return NULL;
}

static char* all_tests() {
  mu_run_test(test_multiplymat4);
  mu_run_test(test_mulmatvec4);
  mu_run_test(test_dotvec4);
  mu_run_test(test_crossvec4);
  mu_run_test(test_rotateX);
  mu_run_test(test_rotateY);
  mu_run_test(test_rotateZ);
  mu_run_test(test_scale);
  mu_run_test(test_translate);
  mu_run_test(test_perspective);
  mu_run_test(test_orthogonal);
  mu_run_test(test_lookAt);
  return NULL;
}

int main(int argc, char **argv)
{

  char *result = all_tests();
  if (result != 0) {

    printf("%s\n", result);

  } else {

    printf("ALL TESTS PASSED\n");

  }

  printf("Tests run: %d\n", tests_run);

  return result != NULL;

}
