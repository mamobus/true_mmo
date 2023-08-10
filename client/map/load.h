#pragma once

#include <string.h>
#include "cute_tiled.h"
#include <malloc.h>
#include <stdint.h>

typedef struct tile_t
{
    float x;
    float y;
    float z;
    float tile_num;
} tile_t;

typedef struct chunk_ram_t
{
    //in bytes
    int shift;
    int tile_count;
} chunk_ram_t;


typedef struct map_t
{
    int width;
    int height;

    chunk_ram_t* chunks;
    tile_t* tiles;
} map_t; 


char* get_tileset_path(char* map_path, char* relative_tileset_path);

void load_map_from_file(char* map_path, map_t* map);

