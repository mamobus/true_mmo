#pragma once

// #include <string.h>
#include <malloc.h>
#include <stdio.h>
// #include <assert.h>
#include <GL/glew.h>
#include "cute_tiled.h"
// #include "../includes/debug_defines.h"
// #include "chunk.h"

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

void load_chunk_manager(FILE* manager_file, chunk_manager_t* chunk_manager) 
{
    // Read the height and width of the 2D array of chunk_t objects from the file
    fread(&chunk_manager->height, sizeof(int), 1, manager_file);
    fread(&chunk_manager->width, sizeof(int), 1, manager_file);

    // Allocate memory for the height*width chunks
    chunk_manager->chunks = calloc(chunk_manager->height * chunk_manager->width, sizeof(chunk_t*));
    // assert(chunk_manager->chunks != 0);

    // Read the 2D array of chunk_t objects from the file
    for (int y = 0; y < chunk_manager->height; y++) 
    {
        for (int x = 0; x < chunk_manager->width; x++) 
        {
            chunk_t* chunk = &(chunk_manager->chunks[x + y*chunk_manager->height]);
            chunk->vbo = 0; // not loaded
            chunk->tiles = NULL; // not loaded

            // Read the chunk's offset and length
            fread(&chunk->offset, sizeof(int), 1, manager_file);
            fread(&chunk->tile_count, sizeof(int), 1, manager_file);
        }
    }
}

void load_chunk(chunk_manager_t* chunk_manager, int x, int y)
{
    //if is loaded
    chunk_t* chunk = &chunk_manager->chunks[x + y*chunk_manager->width];
    if (chunk->tiles != 0)
    {
        return; //cause already loaded
    }
    //so its not loaded
    //now we have buffer
    chunk->tiles = calloc(chunk->tile_count, sizeof(tile_t));
    //lets read into it
    fread(chunk->tiles, sizeof(tile_t), chunk->tile_count, chunk_manager->chunk_file);

    glGenBuffers(1, &chunk->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, chunk->vbo);
    glBufferData(GL_ARRAY_BUFFER, chunk->tile_count * sizeof(tile_t), chunk->tiles, GL_STATIC_DRAW);
}

void free_chunk(chunk_manager_t* chunk_manager, int x, int y)
{
    //if is not loaded
    chunk_t* chunk = &chunk_manager->chunks[x + y*chunk_manager->width];
    if (chunk->tiles == 0)
    {
        return; //cause already unloaded
    }

    free(chunk->tiles);

    glDeleteBuffers(1, &chunk->vbo);
}

void load_all_chunks(chunk_manager_t* chunk_manager)
{
    for(int column=0; column < chunk_manager->width; column++)
    {
        for(int line=0; line < chunk_manager->height; line++)
        {
            load_chunk(chunk_manager, column, line);
        }
    }
}
// typedef struct tile_t
// {
//     float x;
//     float y;
//     float z;
//     float tile_num;
// } tile_t;

// typedef struct chunk_ram_t
// {
//     //in bytes
//     int shift;
//     int tile_count;
// } chunk_ram_t;


// typedef struct map_t
// {
//     int width;
//     int height;

//     chunk_ram_t* chunks;
//     tile_t* tiles;
// } map_t; 


// char* get_tileset_path(char* map_path, char* relative_tileset_path);

// void load_map_from_file(char* map_path, map_t* map);

