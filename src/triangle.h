#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

// ===================================================================
// Type definitions & Variables
// ===================================================================
typedef struct
{
    int a;
    int b;
    int c;
} face_t;

typedef struct
{
    vec2_t points[3];
} triangle_t;

#endif