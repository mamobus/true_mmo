#pragma once

#include <vec.h>

typedef struct item_t
{
    int id;
    int amount;

} item_t;

typedef struct inventory_t
{
    int size;

    item_t* items;

} inventory_t;

typedef struct skill_t
{
    int id;
    int level;
    double timer; //countdown
} skill_t;


// typedef struct stats_t
// {
//     int STR, DEX, AGI, INT, VIT, LUC;
    
//     int 

// } stats_t;

typedef struct player_t
{
    vec3d pos; //местоположение
    vec3d vel; //скорость
    vec3d acl; //ускорение

    vec3d dir;

    int is_grounded;

    int state;

    inventory_t bag;
    // stats_t stats;
} player_t;