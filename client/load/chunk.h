#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <malloc.h>
#include <stdio.h>
#include "cute_tiled.h"
#include <assert.h>
#include "../includes/debug_defines.h"

// #ifdef _DEBUG_
// #define prind(x) printf(x)
// #else
// #define prind(x)
// #endif

typedef struct tile_t
{
    float x, y, z;
    float tile_num;
} tile_t;

typedef struct chunk_t
{
    //those ints are in general not zero
    int offset, tile_count;
    //can be zero and usually is
    tile_t* tiles;
    //can be zero and usually is
    GLuint vbo;
} chunk_t;

//this is 2d array of chunks, some of them are empty, used like hash_table
typedef struct chunk_manager_t
{
    int height, width;
    //2d array of chunk_t
    chunk_t* chunks;
    FILE* chunk_file;
} chunk_manager_t;

//reads manager from file
void load_chunk_manager(char* manager_file_name, char* chunk_file_name, chunk_manager_t* chunk_manager);

void free_chunk_manager(chunk_manager_t* chunk_manager);

//also loads to VBO
void load_chunk(chunk_manager_t* chunk_manager, int x, int y);

//with deleting VBO
void free_chunk(chunk_manager_t* chunk_manager, int x, int y);

void load_all_chunks(chunk_manager_t* chunk_manager);

void free_all_chunks(chunk_manager_t* chunk_manager);