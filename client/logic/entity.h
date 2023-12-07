#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define CVECTOR_LOGARITHMIC_GROWTH
#include <vector.h>
#include <vec.h>
#include <draw/textures/texture_manager.h>
#include <debug_defines.h>

#include <iso646.h>

//std libs

extern mob_typeinfo_t mobinfo[];
#include <math.h>

//structs
#include <common/game_t.h>

#define MOB_CAST_BIT   0b10000000
#define MOB_ATTACK_BIT 0b01000000
#define MOB_MOVE_BIT   0b00100000
#define MOB_STAND_BIT  0b00010000

#define MOB_LEFT_BIT   0b00001000
#define MOB_RIGHT_BIT  0b00000100
#define MOB_UP_BIT     0b00000010
#define MOB_DOWN_BIT   0b00000001

// #define PLAYER_CAST_BIT   0x80
// #define PLAYER_ATTACK_BIT 0x40
// #define PLAYER_MOVE_BIT   0x20
// #define PLAYER_STAND_BIT  0x10

#define PLAYER_ACTION_BITMASK 0xFFF0

#define PLAYER_DEAD_BIT        0x1000
#define PLAYER_PICKUP_BIT       0x800
#define PLAYER_SITTING_BIT      0x400
#define PLAYER_DYING_BIT        0x200
#define PLAYER_CAST_BIT         0x100
#define PLAYER_ATTACK_BIT       0x80
#define PLAYER_MOVE_BIT         0x40
#define PLAYER_ACTIVE_IDLE_BIT  0x20
#define PLAYER_IDLE_BIT         0x10


#define PLAYER_DIRECTION_BITMASK 0xF

#define PLAYER_LEFT_BIT   0x8
#define PLAYER_RIGHT_BIT  0x4
#define PLAYER_UP_BIT     0x2
#define PLAYER_DOWN_BIT   0x1
// #define


#define MOB_ANIMATION_FRAME_TIME 0.18
#define PLAYER_ANIMATION_FRAME_TIME 0.18

void entity_create_manager (game_t* game);
void entity_destroy_manager(game_t* game);

void entity_add(entity_t mob, int type_id, game_t* game);
void entity_del(int id,       int type_id, game_t* game);

void entity_set(entity_t mob, int id, int type_id, game_t* game);
entity_t* entity_find(        int id, int type_id, game_t* game);

void entities_prepare_for_drawing(game_t* game);
