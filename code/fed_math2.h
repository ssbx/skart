#ifndef FED_MATH2_H
#define FED_MATH2_H

typedef struct Mat4 {
    float a0, a1, a2, a3,
          b0 ,b1, b2, b3,
          c0, c1, c2, c3,
          d0, d1, d2, d3;
} Mat4;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

static const Mat4 identityMat4 = {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
};

static const Mat4 emptyMat4 = {
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0
};

Mat4 perspective(
    float fovy,
    float aspect,
    float zNear,
    float zFar);

Mat4 mat4();

Vec3 normalizeVec3(Vec3 vector);

Vec3 crossVec3(
    Vec3 x,
    Vec3 y);

Vec3 minVec3(
    Vec3 a,
    Vec3 b);

Vec3 addVec3(
    Vec3 a,
    Vec3 b);

float dotVec3(
    Vec3 a,
    Vec3 b);

Mat4 lookAt(
    Vec3 eye,
    Vec3 center,
    Vec3 up);

Mat4 multiplyMat4(
    Mat4 mat1,
    Mat4 mat2);

void printMat4(
    Mat4 matrix,
    char* info);

#endif
