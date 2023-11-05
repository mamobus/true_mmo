#pragma once

#include <stdio.h>
#include <GLFW/glfw3.h>

typedef struct block_t
{
    // float x, y, z;
    Vec3 pos;
    float tile_num;
} block_t;

typedef struct chunk_t
{
    //those ints are in general not zero
    int offset, block_count;
    //can be zero and usually is
    block_t* blocks;
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
