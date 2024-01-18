#pragma once

#include <GLFW/glfw3.h>
#include <vec.h>

/*
so we have ecs
what fields can be?
physics component - pos vel mass
animation info
stats
target

*/

typedef struct entity_manager_t 
{
    ecs_world_t* world;
} entity_manager_t;