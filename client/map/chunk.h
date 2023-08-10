#pragma once

#include <malloc.h>
#include <GL/glew.h>
#include "cute_tiled.h"
#include "../common/player.h"
#include "math.h"
#include "load.h"

typedef struct chunk_draw_t
{
    int x;
    int y;
    GLuint vbo;
} chunk_draw_t;

typedef struct chunk_system_t
{
    int x;
    int y;

    chunk_draw_t* draw_chunks;

    map_t map;
} chunk_system_t;

void create_shunk_system();
void load_map_to_chunks(chunk_system_t* chunk_system);
void load_chunk(chunk_draw_t* chunk, int chunk_x, int chunk_y);
void free_chunk(chunk_draw_t* chunk);
void handle_shunk_system(chunk_system_t* chunk_system, player_t player);
