#pragma once

#include <malloc.h>
#include <GL/glew.h>
#include "cute_tiled.h"
#include "../common/player.h"
#include "math.h"

typedef struct tile_elem_t
{
    float x;
    float y;
    float z;
    float tile_num;
} tile_elem_t;

typedef struct chunk_t
{
    int x;                                                                          
    int y;
    int tile_count;

    GLuint vbo_vertex;
    GLuint vbo_uv;

    tile_elem_t* data;
} chunk_t;

typedef struct chunk_system_t
{
    int current_x;
    int current_y;

    int chunk_count;

    chunk_t* chunks;
} chunk_system_t;

chunk_system_t create_shunk_system();
void load_map_to_chunks(chunk_system_t* chunk_system);
void load_chunk(chunk_t* chunk, int chunk_x, int chunk_y);
void free_chunk(chunk_t* chunk);
void handle_shunk_system(chunk_system_t* chunk_system, player_t player);
