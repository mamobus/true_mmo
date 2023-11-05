#pragma once

#include <vec.h>

typedef struct player_t
{
    Vec3 pos; //местоположение
    Vec3 vel; //скорость
    Vec3 acl; //ускорение

    Vec3 dir;

    int is_grounded;
} player_t;