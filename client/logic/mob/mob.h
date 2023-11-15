#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define CVECTOR_LOGARITHMIC_GROWTH
#include <vector.h>
#include <vec.h>
#include <draw/textures/texture_manager.h>
#include <debug_defines.h>

//std libs
#include <math.h>

//structs
#include <common/game_t.h>

#define MOB_CAST_BIT   0b10000000
#define MOB_ATTACK_BIT 0b01000000
#define MOB_MOVE_BIT   0b00100000
#define MOB_STAND_BIT  0b00010000

#define MOB_LEFT_BIT   0b1000
#define MOB_RIGHT_BIT  0b0100
#define MOB_UP_BIT     0b0010
#define MOB_DOWN_BIT   0b0001

#define MOB_ANIMATION_FRAME_TIME 0.18F

void mob_create_manager(game_t* game);
void mob_free_manager  (game_t* game);

void mob_add(mob_t mob, int type_id,                game_t* game);
void mob_del(int id,    int type_id,                game_t* game);

mob_t* mob_find_by_id         (int id,              game_t* game);
mob_t* mob_find_by_id_and_type(int id, int type_id, game_t* game);

void mob_prepare_draw_data(game_t* game);
