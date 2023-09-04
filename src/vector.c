#include <math.h>
#include "vector.h"

vec3_t vec3_rotate_x(vec3_t v, float angle)
{
    vec3_t rotated_vector = {
        v.x,
        v.y * cos(angle) - v.z * sin(angle),
        v.y * sin(angle) + v.z * cos(angle)};
    return rotated_vector;
}

vec3_t vec3_rotate_y(vec3_t v, float angle)
{
    vec3_t rotated_vector = {
        v.x * cos(angle) - v.z * sin(angle),
        v.y,
        v.x * sin(angle) + v.z * cos(angle)};
    return rotated_vector;
}

vec3_t vec3_rotate_z(vec3_t v, float angle)
{
    vec3_t rotated_vector = {
        v.x * cos(angle) - v.y * sin(angle),
        v.x * sin(angle) + v.y * cos(angle),
        v.z};
    return rotated_vector;
}

vec3_t vec3_add(vec3_t a, vec3_t b)
{
    vec3_t result = {
        .x = a.x + b.x,
        .y = b.y + b.y,
        .z = a.z + b.z};

    return result;
}

vec3_t vec3_sub(vec3_t a, vec3_t b)
{
    vec3_t result = {
        .x = a.x - b.x,
        .y = b.y - b.y,
        .z = a.z - b.z};

    return result;
}

vec3_t vec3_mul(vec3_t v, float f)
{
    vec3_t result = {
        .x = v.x * f,
        .y = v.y * f,
        .z = v.z * f,
    };

    return result;
}

vec3_t vec3_div(vec3_t v, float f)
{
    vec3_t result = {
        .x = v.x / f,
        .y = v.y / f,
        .z = v.z / f,
    };

    return result;
}

vec3_t vec3_cross(vec3_t a, vec3_t b)
{
    vec3_t result = {
        .x = a.y * b.z - a.z * b.y,
        .y = a.z * b.x - a.x * b.z,
        .z = a.x * b.y - a.y * b.x};

    return result;
}

float vec3_length(vec3_t v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec2_t vec2_add(vec2_t a, vec2_t b)
{
    vec2_t result = {
        .x = a.x + b.x,
        .y = b.y + b.y};

    return result;
}

vec2_t vec2_sub(vec2_t a, vec2_t b)
{
    vec2_t result = {
        .x = a.x - b.x,
        .y = b.y - b.y};

    return result;
}

vec2_t vec2_mul(vec2_t v, float f)
{
    vec2_t result = {
        .x = v.x * f,
        .y = v.y * f,
    };

    return result;
}

vec2_t vec2_div(vec2_t v, float f)
{
    vec2_t result = {
        .x = v.x / f,
        .y = v.y / f,
    };

    return result;
}

float vec2_length(vec2_t v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

// EOF