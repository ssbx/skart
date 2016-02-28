#include "fed_math2.h"
#include <stdio.h>
#include <stdarg.h>
#include <math.h>


Vec3 normalizeVec3(Vec3 vector)
{

    GLfloat x = vector.x * vector.x;
    GLfloat y = vector.y * vector.y;
    GLfloat z = vector.z * vector.z;
    GLfloat all = x + y + z;

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


GLfloat dotVec3(
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

    Mat4 result = mat4(1);
    result.a0 = s.x;
    result.b0 = s.y;
    result.c0 = s.z;
                    result.a1 = u.x;
                    result.b1 = u.y;
                    result.c1 = u.z;
                                    result.a2 = -f.x;
                                    result.b2 = -f.y;
                                    result.c2 = -f.z;
    result.d0 = -dotVec3(s, eye);
                    result.d1 = -dotVec3(u, eye);
                                    result.d2 = -dotVec3(f, eye);

    return result;

}


Mat4 multiplyMat4(
    Mat4 m1,
    Mat4 m2)
{

    Mat4 result = {
        m1.a0*m2.a0, m1.a1*m2.a1, m1.a2*m2.a2, m1.a3*m2.a3,
        m1.b0*m2.b0, m1.b1*m2.b1, m1.b2*m2.b2, m1.b3*m2.b3,
        m1.c0*m2.c0, m1.c1*m2.c1, m1.c2*m2.c2, m1.c3*m2.c3,
        m1.d0*m2.d0, m1.d1*m2.d1, m1.d2*m2.d2, m1.d3*m2.d3
    };

    return result;

}

static const Mat4 EMPTY_MATRIX_4 = {
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0
};
Mat4 mat4(GLfloat num)
{

    Mat4 result = EMPTY_MATRIX_4;

    result.a0 = num;
                    result.b1 = num;
                                    result.c2 = num;
                                                    result.d3 = num;

    return result;

}


Mat4 perspective(
    GLfloat fovy,
    GLfloat aspect,
    GLfloat zNear,
    GLfloat zFar)
{

    GLfloat tanHalfFovy = tan(fovy / (GLfloat) 2);

    Mat4 result = mat4(0);
    result.a0 = (GLfloat) 1 / (aspect * tanHalfFovy);
    result.b1 = (GLfloat) 1 / (tanHalfFovy);
    result.c2 = - (zFar + zNear) / (zFar - zNear);
    result.c3 = - (GLfloat) 1;
    result.d2 = - ((GLfloat) 2 * zFar * zNear) / (zFar - zNear);

    return result;

}


void printMat4(
    Mat4  matrix,
    char* info)
{

    printf("%s: %f %f %f %f\n", info, matrix.a0, matrix.a1, matrix.a2, matrix.a3);
    printf("%s: %f %f %f %f\n", info, matrix.b0, matrix.b1, matrix.b2, matrix.b3);
    printf("%s: %f %f %f %f\n", info, matrix.c0, matrix.c1, matrix.c2, matrix.c3);
    printf("%s: %f %f %f %f\n", info, matrix.d0, matrix.d1, matrix.d2, matrix.d3);

}
