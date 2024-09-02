#include "hittable/sphere.h"
#include "hittable/hitrecord.h"
#include "ray.h"
#include <math.h>

char sphere_hit(sphere *s, ray *r, float ray_tmin, float ray_tmax, hit_record *rec) {
    vec3 oc = subtract(s->c, r->origin);

    float a    = dot(r->direction, r->direction);
    float h    = dot(r->direction, oc);
    float c    = dot(oc, oc) - s->r * s->r;
    float disc = h * h - a * c;

    if (disc < 0) {
        return 0;
    }

    float sqrtd = sqrt(disc);
    float root  = (h - sqrtd) / a;
    if (root <= ray_tmin || ray_tmax <= root) {
        root = (h + sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root) {
            return 0;
        }
    }

    rec->t = root;
    rec->p = at(*r, root);

    vec3 outward_normal = scale(subtract(rec->p, s->c), 1.0 / s->r);
    set_face_normal(r, outward_normal, rec);

    return 1;
}
