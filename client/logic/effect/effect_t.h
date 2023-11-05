#pragma once

#include <GLFW/glfw3.h>
#include <vec.h>

typedef struct effect_t
{
    Vec3 pos;
    Vec3 vel;

    double last_frame_time;
    int state; // stores bits
    int tile_num; // for drawing
    
    int id; //that is world id, unique for every effect
} effect_t;

typedef struct draw_effect_t
{
    Vec3 pos;
    float tile_num; // for drawing
} draw_effect_t;

typedef struct effect_list_t
{
    int type_id; //that is entity id, same for every effect in list
    GLuint effect_sprite;
    GLuint vbo;
    int sprite_size; //transforms into gl_pointsize insite shaders
    int texture_grid_size;

    //draw_effects in vector. Dont forget to cvector_free
    draw_effect_t* draw_effects;
    //effects in vector. Dont forget to cvector_free
    effect_t* effects;
} effect_list_t;

//effect_listss in vector. Dont forget to cvector_free
typedef effect_list_t* effect_manager_t;