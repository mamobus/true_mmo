#pragma once

#include <GLFW/glfw3.h>
#include "window.h"
#include "../map/cute_tiled.h"
#include "vec.h"

typedef struct draw_buffer
{
    GLuint programID; 
    GLuint tilesetID;
    GLuint textureID;
    GLuint VertexArrayID;
    GLuint vertex_buffer;
    GLuint tile_buffer;
    size_t tile_count;
    // GLuint instance_bufer;
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
