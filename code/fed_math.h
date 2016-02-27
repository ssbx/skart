#ifndef FED_MATH_H
#define FED_MATH_H

/**
 * @file fed_math.h
 * @brief Federation GL mathematics functions.
 */

/**
 * @brief Represent a 4x4 matrix.
 *
 * 0 1 2 3 <br>
 * 4 5 6 7 <br>
 * 8 9 A B <br>
 * C D E F <br>
 */
typedef struct Matrix {
	float m[16];
} Matrix;


/**
 * @brief Represent a x,y,z,w vector.
 */
typedef union Vector4 {
    float m[4];
    struct {
        float x;
        float y;
        float z;
        float w;
    };
} Vector4;

static const Vector4 X_AXIS = {{1, 0, 0, 0}};
static const Vector4 Y_AXIS = {{0, 1, 0, 0}};
static const Vector4 Z_AXIS = {{0, 0, 1, 0}};
static const Vector4 INV_X_AXIS = {{-1, 0, 0, 0}};
static const Vector4 INV_Y_AXIS = {{0, -1, 0, 0}};
static const Vector4 INV_Z_AXIS = {{0, 0, -1, 0}};

static const Matrix IDENTITY_MATRIX = {{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
}};

/**
 * @fn Matrix multiplymat4(const Matrix* ml, const Matrix* m2)
 * @brief Multiply m1 by m2.
 * @returns Matrix, The resulting matrix
 */
Matrix FMath_multiplymat4(
    const Matrix* m1,
    const Matrix* m2);

Vector4 FMath_mulmatvec4(
    const Matrix*  m,
    const Vector4* v);

void FMath_normalizevec4(Vector4* v);

float FMath_dotvec4(
    Vector4 v1,
    Vector4 v2);
Vector4 FMath_crossvec4(
    Vector4 v1,
    Vector4 v2);

void FMath_rotateX(
    Matrix* m,
    float   angle);
void FMath_rotateY(
    Matrix* m,
    float   angle);
void FMath_rotateZ(
    Matrix* m,
    float   angle);

void FMath_scale(
    Matrix* m,
    float   x,
    float   y,
    float   z);
void FMath_translate(
    Matrix* m,
    float   x,
    float   y,
    float   z);

Matrix FMath_perspective(
    float fovy,
    float aspect_ratio,
    float near_plane,
    float far_plane);
Matrix FMath_orthogonal(
    float left,
    float right,
    float bottom,
    float top);

Matrix FMath_lookAt(
    Vector4 pos,
    Vector4 dir);

float FMath_fastSqrt(float number);
float FMath_fastSin(float number);
float FMath_fastCos(float number);

#endif
