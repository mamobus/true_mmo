#pragma once

#include <stdio.h>
#include <GLFW/glfw3.h>

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
