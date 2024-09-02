#include "vec3.h"
#include <math.h>

vec3 add(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

vec3 subtract(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

vec3 scale(vec3 v, float s) {
    vec3 result;
    result.x = v.x * s;
    result.y = v.y * s;
    result.z = v.z * s;

    return result;
}

float dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 cross(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.x * b.z - a.z * b.x;
    result.z = a.x * b.y - a.y * b.x;

    return result;
}

float length(vec3 v) {
    return sqrt(dot(v, v));
}

float lengthSq(vec3 v) {
    return dot(v, v);
}

vec3 normalize(vec3 v) {
    float l = length(v);
    vec3  result;
    result.x = v.x / l;
    result.y = v.y / l;
    result.z = v.z / l;

    return result;
}

void clamp01(vec3 *v) {
    if (v->x < 0.0) {
        v->x = 0.0;
    }
    if (v->x > 1.0) {
        v->x = 1.0;
    }
    if (v->y < 0.0) {
        v->y = 0.0;
    }
    if (v->y > 1.0) {
        v->y = 1.0;
    }
    if (v->z < 0.0) {
        v->z = 0.0;
    }
    if (v->z > 1.0) {
        v->z = 1.0;
    }
}
