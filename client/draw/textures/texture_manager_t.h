#pragma once


#include <GL/glew.h>


/*
    The key reason for this manager to exist is that i dont want same textures to be loaded twice 
    and i also dont want to create mini-managers in every place i need it
*/


//DO NOT ASSIGN ANY VALUES TO ANY OF ENUM VARIABLES. Enum size is TEXTURES_E_SIZE
typedef enum textures_e
{
    TILESET,
    HUD_TEXTURE,
    MOB_STOLEN_GIRL,
    MOB_BLACK_MUSHROOM,
    MOB_GREEN_MUSHROOM,
    MOB_WHITE_MUSHROOM,

    TEXTURES_E_SIZE,
} textures_e;
// #define LAST_TEXTURES_E MOB_WHITE_MUSHROOM

typedef struct texture_cell_t
{
    // int times_loaded;
    GLuint GL_id;
} texture_cell_t;

typedef struct texture_manager_t
{
    texture_cell_t textures[TEXTURES_E_SIZE];
    //trash with countdown
} texture_manager_t;