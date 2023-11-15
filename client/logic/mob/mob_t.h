#pragma once

#include <GLFW/glfw3.h>
#include <vec.h>

typedef struct mob_t
{
    Vec3d pos;
    Vec3d vel;

    double last_frame_time;
    int state; // stores bits
    int tile_num; // for drawing
    
    int id; //that is world id, unique for every mob
} mob_t;

typedef struct draw_mob_t
{
    Vec3f pos;
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