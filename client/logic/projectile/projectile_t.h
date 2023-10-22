#pragma once

#include <GLFW/glfw3.h>
#include <vec.h>

typedef struct projectile_t
{
    Vec3 pos;
    Vec3 vel;
    
    double last_frame_time;
    int state; // stores bits
    int tile_num; // for drawing

    int id; //that is world id, unique for every projectile
    int type_id; //that is entity id, same for every projectile of one type
} projectile_t;

typedef struct draw_projectile_t
{
    Vec3 pos;
    float tile_num; // for drawing
} draw_projectile_t;

typedef struct projectile_manager_t
{
    //we have only one sprite and vbo for all the projectiles
    GLuint projectile_sprite;
    GLuint vbo; 
    int sprite_size; //transforms into gl_pointsize insite shaders
    int texture_grid_size;

    //draw_projectiles in vector. Dont forget to vector_free
    draw_projectile_t* draw_projectiles;

    //projectiles in vector. Dont forget to vector_free
    projectile_t* projectiles;
} projectile_manager_t;