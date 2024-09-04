#include "base64_helper.h"
#include "hittable/hitrecord.h"
#include "hittable/sphere.h"
#include "usefulfn.h"
#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 4096

vec3 frag_color(ray *r);

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

            vec3 color = frag_color(&r);

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

vec3 frag_color(ray *r) {

    sphere s[2];
    s[0].c = ((vec3){.0, .0, .0});
    s[0].r = .2;
    s[1].c = ((vec3){.0, 6.0, 2.5});
    s[1].r = 6.0;

    hit_record rec;
    char       hit_anything = 0;
    float      closest      = 2.0;
    for (int i = 0; i < 2; i += 1) {

        hit_record rec_tmp;
        char       hit = sphere_hit(s + i, r, -2.0, closest, &rec_tmp);
        if (hit) {
            hit_anything = 1;
            closest      = rec_tmp.t;
            rec          = rec_tmp;
        }
    }

    if (hit_anything == 0) {

        vec3 blue;
        blue.x = .5;
        blue.y = .6;
        blue.z = .8;

        vec3 white;
        white.x = .9;
        white.y = .9;
        white.z = .9;

        return mix(blue, white, r->direction.y);
    }

    return subtract(((vec3){.5, .5, .5}), scale(rec.n, .5));
}
