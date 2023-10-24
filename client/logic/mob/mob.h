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

#define MOVE_BIT  0b100000
#define STAND_BIT 0b010000
#define LEFT_BIT  0b001000
#define RIGHT_BIT 0b000100
#define UP_BIT    0b000010
#define DOWN_BIT  0b000001

#define ANIMATION_FRAME_TIME 0.18F

void mob_create_manager(game_t* game);
void mob_free_manager  (game_t* game);

void mob_add(mob_t mob, int type_id,                game_t* game);
void mob_del(int id,    int type_id,                game_t* game);
void mob_set_state(mob_t* mob, int state);

mob_t* mob_find_by_id         (int id,              game_t* game);
mob_t* mob_find_by_id_and_type(int id, int type_id, game_t* game);

void mob_prepare_draw_data(game_t* game);
