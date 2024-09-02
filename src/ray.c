#include "ray.h"

vec3 at(ray r, float t) {
    return add(r.origin, scale(r.direction, t));
}
