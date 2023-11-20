#pragma once

#include <vec.h>

typedef struct player_t
{
    vec3d pos; //местоположение
    vec3d vel; //скорость
    vec3d acl; //ускорение

    vec3d dir;

    int is_grounded;
} player_t;