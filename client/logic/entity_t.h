#pragma once

#include <GLFW/glfw3.h>
#include <vec.h>

typedef union entity_data_t
{
    struct {int   a,b,c,d;};
    struct {float x,y,z,w;};
    char ch[16];
} entity_data_t;

typedef struct entity_t
{
    vec3d pos;
    vec3d vel;

    double last_frame_time;
    int state; // stores bits
    int sprite_num; // for drawing    
    
    int id; //that is world id, unique for every mob

    entity_data_t data;
} entity_t;

typedef struct animinfo_t
{
    int shift;
    int len;
} animinfo_t; 

typedef struct draw_entity_t
{
    vec3f pos;
    float sprite_num; // for drawing
} draw_entity_t; 

typedef struct entity_list_t
{
    int type_id; //that is entity id, same for every mob in list
    GLuint sprite;
    GLuint vbo;
    int sprite_size; //transforms into gl_pointsize insite shaders
    int texture_grid_size;

    //draw_queue in vector. Dont forget to cvector_free
    draw_entity_t* draw_queue;
    //entities in vector. Dont forget to cvector_free
    entity_t* entities;
} entity_list_t;

//they dont have ai and are purely visual
typedef struct cosmetic_list_t
{
    int type_id;
    // int sprite_size; //transforms into gl_pointsize insite shaders
    // int texture_grid_size;
    GLuint sprite;
    GLuint vbo;

    //draw_queue in vector. Dont forget to cvector_free
    draw_entity_t* draw_queue;
} cosmetic_list_t;

//mob_listss in vector. Dont forget to cvector_free
// typedef entity_list_t* entity_manager_t;

typedef struct entity_manager_t 
{
    entity_list_t* elist;

    //things that are drawn on top of entity sprite, such as visual effects, armor or emotion emojis
    cosmetic_list_t* cosmetic;

    GLuint vbo;
    draw_entity_t test;
} entity_manager_t;