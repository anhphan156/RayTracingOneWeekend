#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
    vec3 origin;
    vec3 direction;
} ray;

vec3 at(ray r, float t);

#endif
