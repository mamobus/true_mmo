#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define CVECTOR_LOGARITHMIC_GROWTH
#include <vector.h>
#include <vec.h>
#include <draw/load/load_texture.h>
#include <debug_defines.h>

//std libs
#include <math.h>

//structs
#include <common/game_t.h>

#define EFFECT_START_BIT 0b01
#define EFFECT_GOING_BIT 0b01
#define EFFECT_END_BIT   0b10

#define EFFECT_ANIMATION_FRAME_TIME 0.18F

void effect_create_manager(game_t* game);
void effect_free_manager  (game_t* game);

void effect_add(effect_t effect, int type_id,          game_t* game);
void effect_del(int id,    int type_id,                game_t* game);
 
effect_t* effect_find_by_id         (int id,              game_t* game);
effect_t* effect_find_by_id_and_type(int id, int type_id, game_t* game);

void effect_prepare_draw_data(game_t* game);
