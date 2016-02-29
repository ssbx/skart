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

static char* compare_matrix(Mat4 a, Mat4 b)
{
    mu_assert("error on a0", a.a0 == b.a0);
    mu_assert("error_on a1", a.a1 == b.a1);
    mu_assert("error_on a2", a.a2 == b.a2);
    mu_assert("error_on a3", a.a3 == b.a3);
    mu_assert("error_on b0", a.b0 == b.b0);
    mu_assert("error_on b1", a.b1 == b.b1);
    mu_assert("error_on b2", a.b2 == b.b2);
    mu_assert("error_on b3", a.b3 == b.b3);
    mu_assert("error_on c0", a.c0 == b.c0);
    mu_assert("error_on c1", a.c1 == b.c1);
    mu_assert("error_on c2", a.c2 == b.c2);
    mu_assert("error_on c3", a.c3 == b.c3);
    mu_assert("error_on d0", a.d0 == b.d0);
    mu_assert("error_on d1", a.d1 == b.d1);
    mu_assert("error_on d2", a.d2 == b.d2);
    mu_assert("error_on d3", a.d3 == b.d3);
    return NULL;
}

Mat4 identity = {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1};
static char* test_perspective() {
    Mat4 p = mat4(1);
    return compare_matrix(p, identity);
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

int main(int argc, char *argv)
{

    char *result;
    if (strcmp(argv, "perspective")) {
        return result == NULL;
    }

    result = all_tests();
    if (result != 0) {

        printf("%s\n", result);

    } else {

        printf("ALL TESTS PASSED\n");

    }

    printf("Tests run: %d\n", tests_run);

    return result != NULL;

}
