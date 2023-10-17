#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
// #include "entity.h"
#define CVECTOR_LOGARITHMIC_GROWTH
#include "../includes/vector.h"
#include "../common/vec.h"

//used for drawing. Is changed by what happens with mob
typedef enum mob_state
{
    STAND_LEFT,
    STAND_RIGHT,
    STAND_UP,
    STAND_DOWN,
} mob_state;

typedef struct mob_t
{
    Vec3 pos;
    Vec3 vel;
    int state; // for drawing
    int id; //that is world id, unique for every mob
} mob_t;

typedef struct draw_mob_t
{
    Vec3 pos;
    float state; // for drawing
} draw_mob_t;

typedef struct mob_list_t
{
    int type_id; //that is entity id, same for every mob in list
    GLuint mob_sprite;
    GLuint vbo;

    //draw_mobs in vector. Dont forget to cvector_free
    cvector_vector_type(draw_mob_t) draw_mobs;
    //mobs in vector. Dont forget to cvector_free
    cvector_vector_type(mob_t) mobs;
} mob_list_t;

//mob_listss in vector. Dont forget to cvector_free
typedef cvector_vector_type(mob_list_t) mob_manager_t;


void mob_add(mob_t mob, int type_id,                mob_manager_t mob_manager);
void mob_del(int id,    int type_id,                mob_manager_t mob_manager);
void mob_set_state(mob_t* mob, int state);

mob_t* mob_find_by_id         (int id,              mob_manager_t mob_manager);
mob_t* mob_find_by_id_and_type(int id, int type_id, mob_manager_t mob_manager);

void mob_prepare_draw_data(mob_manager_t mob_manager);
