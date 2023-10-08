#pragma once

// #include <malloc.h>
#include <GL/glew.h>
// #include "cute_tiled.h"
// #include "../common/player.h"
// #include "math.h"
// #include "load.h"

typedef struct tile_t
{
    float x;
    float y;
    float z;
    float tile_num;
} tile_t;

typedef struct chunk_t
{
    int offset, length;
    tile_t* tiles;
    GLuint vbo;
} chunk_t;

//this is 2d array of chunks, some of them are empty, used like hash_table
typedef struct chunk_manager_t
{
    int height, width;

    chunk_t* chunks;

    // map_t map;
} chunk_manager_t;

// void create_shunk_system();
// void load_map_to_chunks(chunk_system_t* chunk_system);
// void load_chunk(chunk_draw_t* chunk, int chunk_x, int chunk_y);
// void free_chunk(chunk_draw_t* chunk);
// void handle_shunk_system(chunk_system_t* chunk_system, player_t player);
