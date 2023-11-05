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

#define PROJECTILE_LEFT_BIT   0b1000
#define PROJECTILE_RIGHT_BIT  0b0100
#define PROJECTILE_UP_BIT     0b0010
#define PROJECTILE_DOWN_BIT   0b0001

#define PROJECTILE_ANIMATION_FRAME_TIME 0.18F

void projectile_create_manager(game_t* game);
void projectile_free_manager  (game_t* game);

void projectile_add(projectile_t projectile, int type_id, game_t* game);
void projectile_del(int id, int type_id, game_t* game);

projectile_t* projectile_find_by_id         (int id,              game_t* game);
projectile_t* projectile_find_by_id_and_type(int id, int type_id, game_t* game);

void projectile_prepare_draw_data(game_t* game);
