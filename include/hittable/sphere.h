#ifndef SPHERE_H
#define SPHERE_H

#include "hittable/hitrecord.h"

typedef struct {
    vec3  c;
    float r;
} sphere;

char sphere_hit(sphere *s, ray *r, float ray_tmin, float ray_tmax, hit_record *rec);

#endif
