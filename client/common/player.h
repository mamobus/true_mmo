#pragma once

#include <vec.h>

typedef struct player_t
{
    Vec3d pos; //местоположение
    Vec3d vel; //скорость
    Vec3d acl; //ускорение

    Vec3d dir;

    int is_grounded;
} player_t;