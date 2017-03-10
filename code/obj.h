/*
 * MIT License
 *
 * LIBOBJ Copyright (c) 2016 Sebastien Serre <ssbx@sysmo.io>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file obj.h
 */
#ifndef OBJ_H
#define OBJ_H

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE   100
#define ARRAY_SIZE_INIT 1000
#define OBJ_TRUE        1
#define OBJ_FALSE       0

typedef struct OBJvec3 {float x, y, z;} OBJvec3;
typedef struct OBJvec2 {float x, y;}    OBJvec2;

/*
 * Variable size int* array
 */
typedef struct Indices {
    unsigned int* i;
    size_t array_size;
    size_t i_count;
} Indices;

/*
 * Variable size OBJvec2* array
 */
typedef struct Vectors2 {
    OBJvec2* v;
    size_t array_size;
    size_t v_count;
} Vectors2;

/*
 * Variable size OBJvec3* array
 */
typedef struct Vectors3 {
    OBJvec3* v;
    size_t array_size;
    size_t v_count;
} Vectors3;

/*
 * The entire scene
 */
typedef struct OBJscene {
    OBJvec3* vertices;
    OBJvec2* uvs;
    OBJvec3* normals;
    size_t   vertices_count;
} OBJscene;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*
 * Portable getline() like function
 */

int
nextline(
    char**  line,
    size_t* line_len,
    FILE*   file)
{
    long int pos_begin;
    char current_char;

    pos_begin = ftell(file);

    int a = 0;
    while(1) {
        a ++;
        current_char = getc(file);
        if (current_char == EOF) {
            return -1;
        }

        if (current_char == '\n') {
            break;
        }
    }

    *line_len = ftell(file) - pos_begin;
    fseek(file, pos_begin, SEEK_SET);

    *line = realloc(*line, ((*line_len + 1) * sizeof(char)));
    fread(*line, sizeof(char), *line_len, file);

    return 0;
}

/*
 * Init alloc utils
 */
void objInitIndices(Indices*   indices);
void objInitVectors2(Vectors2* vectors);
void objInitVectors3(Vectors3* vectors);
void objMaybeReallocIndices(Indices*   indices);
void objMaybeReallocVectors2(Vectors2* vectors);
void objMaybeReallocVectors3(Vectors3* vectors);

OBJscene
objLoad(
        const char* fileName,
        int*        status)
{
    char * line;
    size_t line_len, line_read;
    *status = OBJ_TRUE;

    FILE* objFile = fopen(fileName, "r");

    if (objFile == NULL) {
        printf("Can not read file \n");
        *status = OBJ_FALSE;
        return (OBJscene) {NULL, NULL, NULL, 0};
    }

    // temporary stores
    Vectors3 tmpVertices = {NULL, 0, 0};
    objInitVectors3(&tmpVertices);
    Vectors2 tmpUvs      = {NULL, 0, 0};
    objInitVectors2(&tmpUvs);
    Vectors3 tmpNormals  = {NULL, 0, 0};
    objInitVectors3(&tmpNormals);

    Indices vertexIndices = {NULL, 0, 0};
    objInitIndices(&vertexIndices);
    Indices uvIndices     = {NULL, 0, 0};
    objInitIndices(&uvIndices);
    Indices normalIndices = {NULL, 0, 0};
    objInitIndices(&normalIndices);

    line = NULL; // let getline generate buffer

    while (1) {
        // get the line
        line_read = nextline(&line, &line_len, objFile);

        if (line_read == -1)
            break;

        if (line_read > MAX_LINE_SIZE) {
            printf("Max line size reached\n");
            *status = OBJ_FALSE;
            break;
        }

        // comment
        if (strncmp(line, "#", 1) == 0)
            continue;

        // empty line
        if (strcmp(line, "\n") == 0)
            continue;


        /*
         * VERTEX DATA
         */

        // geometric vertices
        if (strncmp(line, "v ", 2) == 0) {
            objMaybeReallocVectors3(&tmpVertices);

            OBJvec3 vertex;
            sscanf(line, "%*s %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            tmpVertices.v[tmpVertices.v_count] = vertex;
            tmpVertices.v_count ++;
            continue;
        }

        // texture vertices
        if (strncmp(line, "vt ", 3) == 0) {
            objMaybeReallocVectors2(&tmpUvs);

            OBJvec2 uv;
            sscanf(line, "%*s %f %f", &uv.x, &uv.y);
            tmpUvs.v[tmpUvs.v_count] = uv;
            tmpUvs.v_count ++;
            continue;
        }

        // vertex normals
        if (strncmp(line, "vn ", 3) == 0) {
            objMaybeReallocVectors3(&tmpNormals);

            OBJvec3 normal;
            sscanf(line, "%*s %f %f %f\n", &normal.x, &normal.y, &normal.z);
            tmpNormals.v[tmpNormals.v_count] = normal;
            tmpNormals.v_count ++;
            continue;
        }

        // parameter space vertices, Free-form curve/surface attributes
        if (strncmp(line, "vp ", 3) == 0) {
            printf("vp unsupported %s", line);
            continue;
        }

        // rational or non-rational forms of curve or surface type:
        // basis matrix, Bezier, B-spline, Cardinal, Taylor
        if (strncmp(line, "cstype ", 7) == 0 ) {
            printf("cstype unsupported %s", line);
            continue;
        }

        // degree
        if (strncmp(line, "deg ", 4) == 0) {
            printf("deg unsupported %s", line);
            continue;
        }

        // basis matrix
        if (strncmp(line, "bmat ", 5) == 0) {
            printf("bmat unsupported %s", line);
            continue;
        }

        // step size
        if (strncmp(line, "step ", 5) == 0) {
            printf("step unsupported %s", line);
            continue;
        }


        /*
         * ELEMENTS
         */

        // face
        if (strncmp(line, "f ", 2) == 0) // only support triangle faces
        {
            objMaybeReallocIndices(&vertexIndices);
            objMaybeReallocIndices(&uvIndices);
            objMaybeReallocIndices(&normalIndices);

            unsigned int vIndex[3], uvIndex[3], nIndex[3];
            int items = sscanf(line, "%*s %d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &vIndex[0], &uvIndex[0], &nIndex[0],
                    &vIndex[1], &uvIndex[1], &nIndex[1],
                    &vIndex[2], &uvIndex[2], &nIndex[2]);

            if (items != 9) {
                printf("Error Only andle triangle faces\n");

                *status = OBJ_FALSE;
                break;
            }

            vertexIndices.i[vertexIndices.i_count]     = vIndex[0];
            vertexIndices.i[vertexIndices.i_count + 1] = vIndex[1];
            vertexIndices.i[vertexIndices.i_count + 2] = vIndex[2];
            vertexIndices.i_count += 3;

            uvIndices.i[uvIndices.i_count]     = uvIndex[0];
            uvIndices.i[uvIndices.i_count + 1] = uvIndex[1];
            uvIndices.i[uvIndices.i_count + 2] = uvIndex[2];
            uvIndices.i_count += 3;

            normalIndices.i[normalIndices.i_count]     = nIndex[0];
            normalIndices.i[normalIndices.i_count + 1] = nIndex[1];
            normalIndices.i[normalIndices.i_count + 2] = nIndex[2];
            normalIndices.i_count += 3;

            continue;
        }

        // point
        if (strncmp(line, "p ", 2) == 0) {
            printf("p unsupported %s", line);
            continue;
        }

        // line
        if (strncmp(line, "l ", 2) == 0) {
            printf("line unsupported %s", line);
            continue;
        }

        // curve
        if (strncmp(line, "curv ", 5) == 0) {
            printf("curv unsupported %s", line);
            continue;
        }

        // 2D curve
        if (strncmp(line, "curv2 ", 6) == 0) {
            printf("curv2 unsupported %s", line);
            continue;
        }

        // surface
        if (strncmp(line, "surf ", 5) == 0) {
            printf("surf unsupported %s", line);
            continue;
        }

        /*
         * FREE-FORM CUURVE/SURFACE BODY STATEMENTS
         */

        // parameter values
        if (strncmp(line, "parm ", 5) == 0) {
            printf("parm unsupported %s", line);
            continue;
        }

        // outer trimming loop
        if (strncmp(line, "trim ", 5) == 0) {
            printf("trim unsupported %s", line);
            continue;
        }

        // inner trimming loop
        if (strncmp(line, "loop ", 5) == 0) {
            printf("loop unsupported %s", line);
            continue;
        }

        // special curve
        if (strncmp(line, "scrv ", 5) == 0) {
            printf("surf unsupported %s", line);
            continue;
        }

        // special point
        if (strncmp(line, "sp ", 3) == 0) {
            printf("sp unsupported %s", line);
            continue;
        }

        // end statement
        if (strncmp(line, "end ", 4) == 0) {
            printf("end unsupported %s", line);
            continue;
        }

        /*
         * CONNECTIVITY BETWEEN FREE-FORM SURFACES
         */

        // connect
        if (strncmp(line, "con ", 3) == 0) {
            printf("con unsupported %s", line);
            continue;
        }

        /*
         * DISPLAY/RENDER ATTRIBUTES
         */

        // bevel interpolation
        if (strncmp(line, "bevel ", 6) == 0) {
            printf("bevel unsupported %s", line);
            continue;
        }

        // color interpolation
        if (strncmp(line, "c_interp ", 9) == 0) {
            printf("c_interp unsupported %s", line);
            continue;
        }

        // dissolve interolation
        if (strncmp(line, "d_interp ", 9) == 0) {
            printf("d_interp unsupported %s", line);
            continue;
        }

        // level of detail
        if (strncmp(line, "lod ", 4) == 0) {
            printf("lod unsupported %s", line);
            continue;
        }

        // material name
        if (strncmp(line, "usemtl ", 7) == 0) {
            printf("usemtl unsupported %s", line);
            continue;
        }

        // material library
        if (strncmp(line, "mtllib ", 7) == 0) {
            printf("mtllib unsupported %s", line);
            continue;
        }

        // shadow casting
        if (strncmp(line, "shadow_obj ", 11) == 0) {
            printf("shadow_obj unsupported %s", line);
            continue;
        }

        // ray tracing
        if (strncmp(line, "trace_obj ", 10) == 0) {
            printf("trace_obj unsupported %s", line);
            continue;
        }

        // curve approximation technique
        if (strncmp(line, "ctech ", 6) == 0) {
            printf("ctech unsupported %s", line);
            continue;
        }

        // survace approximation technique
        if (strncmp(line, "stech ", 6) == 0) {
            printf("stech unsupported %s", line);
            continue;
        }


        /*
         * GROUPING
         */

        // object
        if (strncmp(line, "o ", 2) == 0) {
            printf("object unsupported %s", line);
            continue;
        }

        // group
        if (strncmp(line, "g ", 2) == 0) {
            printf("group unsupported %s", line);
            continue;
        }

        // smooth group
        if (strncmp(line, "s ", 2) == 0) {
            printf("smooth group unsupported %s", line);
            continue;
        }

        // merging group
        if (strncmp(line, "mg ", 3) == 0) {
            printf("merging group unsupported %s", line);
            continue;
        }

        // else
        printf("unknown type %s", line);

    } // while(1)


    OBJscene scene = {NULL, NULL, NULL, 0};
    if (*status != OBJ_FALSE) {
        // create the return value
        scene.vertices_count = vertexIndices.i_count;
        scene.vertices       = malloc(vertexIndices.i_count * sizeof(OBJvec3));
        scene.uvs            = malloc(vertexIndices.i_count * sizeof(OBJvec2));
        scene.normals        = malloc(vertexIndices.i_count * sizeof(OBJvec3));

        // fill return buffers
        unsigned int index, vertexIndex, uvIndex, normalIndex;
        for (
                index = 0;
                index < vertexIndices.i_count;
                index ++)
        {
            vertexIndex = vertexIndices.i[index];
            uvIndex     = uvIndices.i[index];
            normalIndex = normalIndices.i[index];

            OBJvec3 vertex = tmpVertices.v[vertexIndex - 1];
            OBJvec2 uv     = tmpUvs.v[vertexIndex - 1];
            OBJvec3 normal = tmpNormals.v[vertexIndex - 1];

            scene.vertices[index] = vertex;
            scene.uvs[index]      = uv;
            scene.normals[index]  = normal;
        }
    }

    // cleanup
    if (line != NULL)
        free(line);

    if (vertexIndices.i != NULL)
        free(vertexIndices.i);

    if (uvIndices.i != NULL)
        free(uvIndices.i);

    if (normalIndices.i != NULL)
        free(normalIndices.i);

    if (tmpNormals.v != NULL)
        free(tmpNormals.v);

    if (tmpUvs.v != NULL)
        free(tmpUvs.v);

    if (tmpVertices.v != NULL)
        free(tmpVertices.v);

    fclose(objFile);

    return scene;
}


void
objRelease(OBJscene scene)
{
    if (scene.uvs != NULL)
        free(scene.uvs);

    if (scene.normals != NULL)
        free(scene.normals);

    if (scene.vertices != NULL)
        free(scene.vertices);
}

/*
 * Initialize OBJvec3 array store
 */
void
objInitVectors3(Vectors3* vectors)
{
    vectors->array_size = ARRAY_SIZE_INIT;
    vectors->v = realloc(vectors->v,
            vectors->array_size * sizeof(OBJvec3));
}

/*
 * Initialize OBJvec2 array store
 */
void
objInitVectors2(Vectors2* vectors)
{
    vectors->array_size = ARRAY_SIZE_INIT;
    vectors->v = realloc(vectors->v,
            vectors->array_size * sizeof(OBJvec2));
}

/*
 * Initialize Indices array store
 */
void
objInitIndices(Indices* indices)
{
    indices->array_size = ARRAY_SIZE_INIT;
    indices->i = realloc(indices->i,
            indices->array_size * sizeof(unsigned int));
}

/*
 * Maybe realoc vector3 array
 */
void
objMaybeReallocVectors3(Vectors3* vectors)
{
    if (vectors->array_size == vectors->v_count) {
        vectors->array_size = vectors->array_size * 2;
        vectors->v = realloc(vectors->v,
                vectors->array_size * sizeof(OBJvec3));
    }
}

/*
 * Maybe realoc vector2 array
 */
void
objMaybeReallocVectors2(Vectors2* vectors)
{
    if (vectors->array_size == vectors->v_count) {
        vectors->array_size = vectors->array_size * 2;
        vectors->v = realloc(vectors->v,
                vectors->array_size * sizeof(OBJvec2));
    }
}

/*
 * Maybe realoc Indices array
 */
void
objMaybeReallocIndices(Indices* indices)
{
    // indices are filled 3 by 3
    int offset = 3;
    if (indices->array_size < indices->i_count + offset) {
        indices->array_size = indices->array_size * 2;
        indices->i = realloc(indices->i,
                indices->array_size * sizeof(unsigned int));
    }
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LIBOBJ_H

