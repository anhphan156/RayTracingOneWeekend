#ifndef VEC3_H
#define VEC3_H

typedef struct {
    float x;
    float y;
    float z;
} vec3;

vec3  add(vec3, vec3);
vec3  subtract(vec3, vec3);
vec3  scale(vec3, float);
float dot(vec3, vec3);
vec3  cross(vec3, vec3);
vec3  normalize(vec3);
float length(vec3);
float lengthSq(vec3);
void  clamp01(vec3 *);

#endif
