#include "hittable/hitrecord.h"

void set_face_normal(ray *r, vec3 outward_normal, hit_record *rec) {
    rec->front_face = dot(r->direction, outward_normal) < 0;
    rec->n          = rec->front_face ? outward_normal : scale(outward_normal, -1.0);
}
