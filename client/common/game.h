#pragma once

#include <GLFW/glfw3.h>
#include "window.h"
#include "../map/cute_tiled.h"
#include "vec.h"

typedef struct uniforms_t
{
    GLuint textureID;
    GLuint camera_coords;
    // GLuint textureID;
} uniforms_t;


typedef struct draw_buffer
{
    GLuint programID; 
    GLuint tilesetID;
    GLuint VertexArrayID;
    GLuint vertex_buffer;
    GLuint tile_buffer;
    size_t tile_count;

    uniforms_t uni;
    
    Vec3* vertex_data;
    float* tile_data;
} draw_buffer;

typedef struct Game_t
{
    Window_t window;
    cute_tiled_map_t* map;
    draw_buffer draw;
} Game_t;

void give_this_game_a_window(Game_t* game);
