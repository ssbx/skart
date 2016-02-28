#include "fed_math.h"

#include <math.h>
#include <string.h>
#include <stdio.h>

static const double PI = 3.14159265358979323846;


Matrix fedMultiplymat4(
    const Matrix* m1,
    const Matrix* m2)
{

    Matrix out = IDENTITY_MATRIX;
    unsigned int row;
    unsigned int column;
    unsigned int row_offset;

    for (row = 0; row < 4; ++row)
    {

        row_offset = row * 4;

        for (column = 0; column < 4; ++column)
        {

            out.m[row_offset + column] =
            (m1->m[row_offset + 0] * m2->m[column + 0]) +
            (m1->m[row_offset + 1] * m2->m[column + 4]) +
            (m1->m[row_offset + 2] * m2->m[column + 8]) +
            (m1->m[row_offset + 3] * m2->m[column + 12]);

        }

    }

    return out;

}


Vector4 fedMulmatvec4(
    const Matrix*  m,
    const Vector4* v)
{
    Vector4 out;

    int i;
    for(i = 0; i < 4; ++i)
    {

        out.m[i] =
        (v->m[0] * m->m[i + 0]) +
        (v->m[1] * m->m[i + 4]) +
        (v->m[2] * m->m[i + 8]) +
        (v->m[3] * m->m[i + 12]);

    }

    return out;

}


void fedNormalizevec4(Vector4* v)
{

    float sqr = v->m[0] * v->m[0] + v->m[1] * v->m[1] + v->m[2] * v->m[2];

    if(sqr == 1 || sqr == 0) return;

    float invrt = 1.f/sqrt(sqr);
    v->m[0] *= invrt;
    v->m[1] *= invrt;
    v->m[2] *= invrt;

}


float fedDotvec4(
    Vector4 v1,
    Vector4 v2)
{

    return v1.m[0] * v2.m[0] + v1.m[1] * v2.m[1] + v1.m[2] * v2.m[2] +
    v1.m[3] * v2.m[3];

}


Vector4 fedCrossvec4(
    Vector4 v1,
    Vector4 v2)
{

    Vector4 out = {{0}};

    out.m[0] = v1.m[1]*v2.m[2] - v1.m[2]*v2.m[1];
    out.m[1] = v1.m[2]*v2.m[0] - v1.m[0]*v2.m[2];
    out.m[2] = v1.m[0]*v2.m[1] - v1.m[1]*v2.m[0];
    return out;

}


void fedRotateX(
    Matrix* m,
    float   angle)
{

    Matrix rotation = IDENTITY_MATRIX;
    float sine = (float)sin(angle);
    float cosine = (float)cos(angle);

    rotation.m[5] = cosine;
    rotation.m[6] = -sine;
    rotation.m[9] = sine;
    rotation.m[10] = cosine;

    Matrix result = fedMultiplymat4(m, &rotation);
    memcpy(m->m, result.m, sizeof(m->m));

}


void fedRotateY(
    Matrix* m,
    float   angle)
{

    Matrix rotation = IDENTITY_MATRIX;
    float sine = (float)sin(angle);
    float cosine = (float)cos(angle);

    rotation.m[0] = cosine;
    rotation.m[8] = sine;
    rotation.m[2] = -sine;
    rotation.m[10] = cosine;

    Matrix result = fedMultiplymat4(m, &rotation);

    memcpy(m->m, result.m, sizeof(m->m));

}


void fedRotateZ(
    Matrix* m,
    float   angle)
{

    Matrix rotation = IDENTITY_MATRIX;
    float sine = (float)sin(angle);
    float cosine = (float)cos(angle);

    rotation.m[0] = cosine;
    rotation.m[1] = -sine;
    rotation.m[4] = sine;
    rotation.m[5] = cosine;

    Matrix result = fedMultiplymat4(m, &rotation);
    memcpy(m->m, result.m, sizeof(m->m));

}


void fedScale(
    Matrix* m,
    float   x,
    float   y,
    float   z)
{

    Matrix scale = IDENTITY_MATRIX;
    scale.m[0] = x;
    scale.m[5] = y;
    scale.m[10] = z;

    Matrix result = fedMultiplymat4(m, &scale);
    memcpy(m->m, result.m, sizeof(m->m));

}


void fedTranslate(
    Matrix* m,
    float   x,
    float   y,
    float   z)
{

    Matrix translation = IDENTITY_MATRIX;

    translation.m[12] = x;
    translation.m[13] = y;
    translation.m[14] = z;

    Matrix result = fedMultiplymat4(m, &translation);
    memcpy(m->m, result.m, sizeof(m->m));

}


Matrix fedPerspective(
    float fovy,
    float aspect_ratio,
    float near_plane,
    float far_plane)
{

    Matrix out = { { 0 } };

    const float y_scale        = (float)(1/cos(fovy * PI / 360));
    const float x_scale        = y_scale / aspect_ratio;
    const float frustum_length = far_plane - near_plane;

    out.m[0] = x_scale;
    out.m[5] = y_scale;
    out.m[10] = -((far_plane + near_plane) / frustum_length);
    out.m[11] = -1;
    out.m[14] = -((2 * near_plane * far_plane) / frustum_length);

    return out;

}


Matrix fedOrthogonal(
    float left,
    float right,
    float bottom,
    float top)
{

    Matrix out = IDENTITY_MATRIX;
    out.m[0] = 2 / (right - left);
    out.m[5] = 2 / (top - bottom);
    out.m[10] = -1;
    out.m[12] = - (right + left) / (right - left);
    out.m[13] = - (top + bottom) / (top - bottom);

    return out;

}


Matrix fedLookAt(
    Vector4 pos,
    Vector4 dir)
{

    Vector4 f = dir;
    fedNormalizevec4(&f);
    Vector4 u = {{0, 1, 0, 0}};
    Vector4 s = fedCrossvec4(f, u);
    fedNormalizevec4(&s);
    u = fedCrossvec4(s, f);

    Matrix out = IDENTITY_MATRIX;
    out.m[0] = s.x;
    out.m[4] = s.y;
    out.m[8] = s.z;

    out.m[1] = u.x;
    out.m[5] = u.y;
    out.m[9] = u.z;

    out.m[2] = -f.x;
    out.m[6] = -f.y;
    out.m[10] = -f.z;

    out.m[12] = -fedDotvec4(s, pos);
    out.m[13] = -fedDotvec4(u, pos);
    out.m[14] =  fedDotvec4(f, pos);

    return out;

}


float fedFastSqrt(float number)
{

    /*
     * Copyed from https://en.wikipedia.org/wiki/Fast_inverse_square_root
     */

    long  i;
    float x2;
    float y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;

    // evil floating point bit level hacking
    i  = *(long*) &y;

    // what the fuck?
    i  = 0x5f3759df - (i >> 1);

    y  = * (float*) &i;

    // 1st iteration
    y  = y * (threehalfs - (x2 * y * y));

    // 2nd iteration, this can be removed
    // y  = y * (threehalfs - (x2 * y * y));

    return y;

}

void fedPrintMat(Matrix mat, char* tag)
{
    printf("\n\n%s\n", tag);
    printf("%f %f %f %f\n", mat.m[0], mat.m[1], mat.m[2], mat.m[3]);
    printf("%f %f %f %f\n", mat.m[4], mat.m[5], mat.m[6], mat.m[7]);
    printf("%f %f %f %f\n", mat.m[8], mat.m[9], mat.m[10], mat.m[11]);
    printf("%f %f %f %f\n", mat.m[12], mat.m[13], mat.m[14], mat.m[15]);
    printf("end %s\n\n", tag);

}
