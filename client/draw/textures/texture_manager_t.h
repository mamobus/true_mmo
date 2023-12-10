#pragma once


#include <GL/glew.h>


/*
    The key reason for this manager to exist is that i dont want same textures to be loaded twice 
    and i also dont want to create mini-managers in every place i need it
*/


// enum mobs_e
// {
//     MOB_UNDEF = 0,
//     MOB_PLAYER = 1,
//     MOB_BLACK_MUSHROOM = 2,
//     MOB_WHITE_MUSHROOM = 3,
// };

//DO NOT ASSIGN ANY VALUES TO ANY OF ENUM VARIABLES. Enum size is TEXTURES_E_SIZE

typedef enum textures_e
{
    TEXTURE_HUD         =0,
    TEXTURE_TILESET     =1,

    TEXTURE_PLAYER      =101,
    TEXTURE_PLAYER_HEADS=103,


    #define mob(type_id, name, texture, pixel_H, pixel_W, texture_H, texture_W, stand_frames, move_frames, attack_frames, cast_frames, death_frames, ...) \
    TEXTURE_MOB_##name=type_id,
    #include <_lists/moblist.h>


    // TEXTURES_E_SIZE,
} textures_e;
// // #define LAST_TEXTURES_E MOB_WHITE_MUSHROOM

// typedef struct texture_cell_t
// {
//     int times_loaded;
//     GLuint GL_id;
// } texture_cell_t;

// typedef struct texture_manager_t
// {
//     texture_cell_t textures[TEXTURES_E_SIZE];
//     //trash with countdown
// } texture_manager_t;