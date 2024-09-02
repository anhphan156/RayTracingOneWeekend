#include "usefulfn.h"
#include "vec3.h"

vec3 mix(vec3 a, vec3 b, float t) {
    return add(scale(a, 1.0 - t), scale(b, t));
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
