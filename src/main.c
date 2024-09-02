#include "base64_helper.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 4096

float hit_sphere(vec3 sphere_center, float radius, ray r);
vec3  frag_color(ray r);

int main() {

    int w = 1024;
    int h = 1024;

    // ray tracing setup
    vec3 cam_pos = ((vec3){0.0, 0.0, -2.0});

    ray r;
    r.origin = cam_pos;

    // image buffer setup
    size_t         byte_data_size = 3 * w * h;
    unsigned char *byte_data      = malloc(byte_data_size);
    unsigned char *ptr            = byte_data;

    for (int y = 0; y < h; y += 1) {
        for (int x = 0; x < w; x += 1) {

            vec3 uv;
            uv.x = ((float)x / ((float)w - 1.0)) - .5;
            uv.y = ((float)y / ((float)h - 1.0)) - .5;
            uv.z = 0.0;

            r.direction = subtract(uv, r.origin);

            vec3 color = frag_color(r);

            clamp01(&color);

            ptr[0] = color.x * 255.999;
            ptr[1] = color.y * 255.999;
            ptr[2] = color.z * 255.999;

            ptr += 3;
        }
    }

    size_t base64_length;
    char  *base64_string = base64_encode(byte_data, byte_data_size, &base64_length);
    char  *ptr2          = base64_string;

    printf("\033_Ga=T,f=24,s=%d,v=%d,m=1;\033\\", w, h);
    while (base64_length > 0) {
        size_t write_size = CHUNK_SIZE < base64_length ? CHUNK_SIZE : base64_length;
        printf("\033_Gm=%i;", base64_length == 4096 ? 0 : 1);
        fwrite(ptr2, sizeof(char), write_size, stdout);
        printf("\033\\");

        ptr2 += write_size;
        base64_length -= write_size;
    }

    /*printf("\n");*/
    /*printf("\033_Gf=24,s=%d,v=%d,a=T;%s\033\\", w, h, base64_string);*/
    printf("\n");

    free(byte_data);
    free(base64_string);

    return 0;
}

vec3 frag_color(ray r) {

    vec3  sphere_center = ((vec3){.0, .0, .0});
    float radius        = .3;

    vec3  color;
    float t = hit_sphere(sphere_center, radius, r);

    if (t < 0) {

        color.x = r.direction.x;
        color.y = r.direction.y;
        color.z = 0.0;

        return color;
    }

    vec3 p = at(r, t);
    vec3 n = normalize(subtract(sphere_center, p));
    n      = add(((vec3){.5, .5, .5}), scale(n, .5));

    return n;
}

float hit_sphere(vec3 sphere_center, float radius, ray r) {
    vec3 oc = subtract(sphere_center, r.origin);

    float a    = dot(r.direction, r.direction);
    float h    = dot(r.direction, oc);
    float c    = dot(oc, oc) - radius * radius;
    float disc = h * h - a * c;

    if (disc < 0) {
        return -1.0;
    } else {
        return (h - sqrt(disc)) / a;
    }
}
