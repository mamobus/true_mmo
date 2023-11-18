#pragma once 
/*
entity package:
state (is mob or projectile or skill or player etc..., then pos \ vel)
if info package, than just info type, size and finally data
*/
#define CVECTOR_LOGARITHMIC_GROWTH
#include <vector.h>
#include <vec.h>
#include <draw/textures/texture_manager.h>
#include <debug_defines.h>

//std libs
#include <math.h>

//structs
#include <common/game_t.h>

void net_create_manager(game_t* game);

void net_update(game_t* game);