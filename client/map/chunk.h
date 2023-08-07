#pragma once

#include <malloc.h>
#include <GL/glew.h>
#include "cute_tiled.h"

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

    GLuint vbo;

    tile_elem_t* data;
} chunk_t;

typedef struct chunk_system_t
{
    //if high then old chunks are not unloaded immideatly
    int max;
    //if high then pre-uploads chunks
    int min;

    int current_x;
    int current_y;

    chunk_t* chunks;
} chunk_system_t;

chunk_t load_chunk_from_sql(int x, int y);
chunk_system_t* create_shunk_system();
void load_map_to_chunks(chunk_system_t* chunk_system);
void load_chunk(chunk_system_t* chunk_system, int chunk_x, int chunk_y, int chunk_num);
void free_chunk(chunk_system_t* chunk_system, int chunk_x, int chunk_y, int chunk_num);
void handle_shunk_system(chunk_system_t* chunk_system);
