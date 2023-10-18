#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
// #include "entity.h"
#define CVECTOR_LOGARITHMIC_GROWTH
#include "../includes/vector.h"
#include "../client/draw/load/load_texture.h"
#include "../common/vec.h"

#include "../includes/debug_defines.h"

//used for drawing. Is changed by what happens with mob
// typedef enum mob_state
// {
//     STAND_LEFT,
//     STAND_RIGHT,
//     STAND_,
//     STAND_,
//     MOVE_LEFT
//     MOVE_RIGHT
//     MOVE_
//     MOVE_
//     LEFT
//     RIGHT   
//     UP  
//     DOWN    
// } mob_state;
#define _sep_

#define MOVE_BIT  0b100000
#define STAND_BIT 0b010000
#define LEFT_BIT  0b001000
#define RIGHT_BIT 0b000100
#define UP_BIT    0b000010
#define DOWN_BIT  0b000001

#define ANIMATION_FRAME_TIME 0.18F

typedef struct mob_t
{
    Vec3 pos;
    Vec3 vel;
    double last_frame_time;
    int state; // stores bits
    int tile_num; // for drawing
    int id; //that is world id, unique for every mob
} mob_t;

typedef struct draw_mob_t
{
    Vec3 pos;
    float tile_num; // for drawing
} draw_mob_t;

typedef struct mob_list_t
{
    int type_id; //that is entity id, same for every mob in list
    GLuint mob_sprite;
    GLuint vbo;
    int sprite_size; //transforms into gl_pointsize insite shaders
    int texture_grid_size;

    //draw_mobs in vector. Dont forget to cvector_free
    draw_mob_t* draw_mobs;
    //mobs in vector. Dont forget to cvector_free
    mob_t* mobs;
} mob_list_t;

//mob_listss in vector. Dont forget to cvector_free
typedef mob_list_t* mob_manager_t;


void mob_add(mob_t mob, int type_id,                mob_manager_t* mob_manager);
void mob_del(int id,    int type_id,                mob_manager_t mob_manager);
void mob_set_state(mob_t* mob, int state);

mob_t* mob_find_by_id         (int id,              mob_manager_t mob_manager);
mob_t* mob_find_by_id_and_type(int id, int type_id, mob_manager_t mob_manager);

void mob_prepare_draw_data(mob_manager_t mob_manager);
