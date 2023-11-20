#pragma once


#include <vec.h>

//use code generation for client & server the same time
/*
vec3 pos, tile_num and bind the texture

and manage textures that are loaded in manager

array for managing
array of arrays of vbo data
*/

typedef struct entity_t
{
    vec3f position;
    vec3f velocity;
    int id;
} entity_t;