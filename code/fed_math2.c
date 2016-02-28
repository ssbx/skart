#include "fed_math2.h"
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

Vec3 normalizeVec3(Vec3 vector)
{
    float x = vector.x * vector.x;
    float y = vector.y * vector.y;
    float z = vector.z * vector.z;
    float all = x + y + z;
    Vec3 result;
    result.x = vector.x / all;
    result.y = vector.y / all;
    result.z = vector.z / all;

    return result;
}

Vec3 crossVec3(
    Vec3 x,
    Vec3 y)
{
    Vec3 result;
    result.x = x.y * y.z - y.y * x.z;
    result.y = x.z * y.x - y.z * x.x;
    result.z = x.x * y.y - y.x * x.y;

    return result;
}

Vec3 minusVec3(
    Vec3 a,
    Vec3 b)
{
    Vec3 result;
    result.x = a.x + (0 - b.x);
    result.y = a.y + (0 - b.y);
    result.z = a.z + (0 - b.z);

    return result;
}

Vec3 addVec3(
    Vec3 a,
    Vec3 b)
{
    Vec3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

float dotVec3(
    Vec3 a,
    Vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Mat4 lookAt(
    Vec3 eye,
    Vec3 center,
    Vec3 up)
{
    const Vec3 f = normalizeVec3(minusVec3(center, eye));
    const Vec3 s = normalizeVec3(crossVec3(f, up));
    const Vec3 u = crossVec3(s, f);

    Mat4 result = mat4();

    result.a0 = s.x;
    result.b0 = s.y;
    result.c0 = s.z;
    result.a1 = u.x;
    result.b1 = u.y;
    result.c1 = u.z;
    result.a2 =-f.x;
    result.b2 =-f.y;
    result.c2 =-f.z;
    result.d0 = -dotVec3(s, eye);
    result.d1 = -dotVec3(u, eye);
    result.d2 = -dotVec3(f, eye);

    return result;
}

Mat4 multiplyMat4(
    Mat4 mat1,
    Mat4 mat2)
{
    Mat4 result;
    result.a0 = mat1.a0 * mat2.a0;
    result.a1 = mat1.a1 * mat2.a1;
    result.a2 = mat1.a2 * mat2.a2;
    result.a3 = mat1.a3 * mat2.a3;
    result.b0 = mat1.b0 * mat2.b0;
    result.b1 = mat1.b1 * mat2.b1;
    result.b2 = mat1.b2 * mat2.b2;
    result.b3 = mat1.b3 * mat2.b3;
    result.c0 = mat1.c0 * mat2.c0;
    result.c1 = mat1.c1 * mat2.c1;
    result.c2 = mat1.c2 * mat2.c2;
    result.c3 = mat1.c3 * mat2.c3;
    result.d0 = mat1.d0 * mat2.d0;
    result.d1 = mat1.d1 * mat2.d1;
    result.d2 = mat1.d2 * mat2.d2;
    result.d3 = mat1.d3 * mat2.d3;
    return result;
}

Mat4 mat4()
{
    Mat4 r = identityMat4;
    return r;
}

Mat4 perspective(
    float fovy,
    float aspect,
    float zNear,
    float zFar)
{
    float tanHalfFovy = tan(fovy / 2.0f);
    Mat4 result = emptyMat4;
    result.a0 = 1.0f / (aspect * tanHalfFovy);
    result.b1 = 1.0f / (tanHalfFovy);
    result.c2 = - (zFar + zNear) / (zFar - zNear);
    result.c3 = - 1.0f;
    result.d2 = - (2.0f * zFar * zNear) / (zFar - zNear);
    return result;

}

void printMat4(
    Mat4  matrix,
    char* info)
{
    printf("\n\n%s\n", info);
    printf("%f %f %f %f\n", matrix.a0, matrix.a1, matrix.a2, matrix.a3);
    printf("%f %f %f %f\n", matrix.b0, matrix.b1, matrix.b2, matrix.b3);
    printf("%f %f %f %f\n", matrix.c0, matrix.c1, matrix.c2, matrix.c3);
    printf("%f %f %f %f\n", matrix.d0, matrix.d1, matrix.d2, matrix.d3);
}
