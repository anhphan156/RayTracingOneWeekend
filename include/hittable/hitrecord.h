#ifndef HITRECORD_H
#define HITRECORD_H

#include "ray.h"
#include "vec3.h"

typedef struct {
    vec3  p;
    vec3  n;
    float t;

    char front_face;
} hit_record;

void set_face_normal(ray *r, vec3 outward_normal, hit_record *rec);

#endif
