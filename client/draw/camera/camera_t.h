#pragma once

#include <vec.h>

typedef struct camera_t
{
    vec3d shift;
    vec3d position;
    vec3d velocity;
} camera_t;