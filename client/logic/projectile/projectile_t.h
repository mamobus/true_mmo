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
} projectile_t;

typedef struct draw_projectile_t
{
    Vec3 pos;
    float tile_num; // for drawing
} draw_projectile_t;

typedef struct projectile_list_t
{
    int type_id; //that is entity id, same for every projectile in list
    GLuint projectile_sprite;
    GLuint vbo;
    int sprite_size; //transforms into gl_pointsize insite shaders
    int texture_grid_size;

    //draw_projectiles in vector. Dont forget to cvector_free
    draw_projectile_t* draw_projectiles;
    //projectiles in vector. Dont forget to cvector_free
    projectile_t* projectiles;
} projectile_list_t;

//projectile_listss in vector. Dont forget to cvector_free
typedef projectile_list_t* projectile_manager_t;