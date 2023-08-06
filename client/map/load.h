#pragma once

// #include <GL/glew.h>
#include "../common/game.h"
#include <string.h>
// #include "../draw/load_texture.h"
#include "../map/cute_tiled.h"
#include <malloc.h>


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

char* get_tileset_path(char* map_path, char* relative_tileset_path);

void load_level(Game_t* game);

void free_level(Game_t* game);


chunk_t load_chunk_from_sql(int x, int y);
void create_shunk_system();
void load_map_to_chunks();
void load_chunk();
void free_chunk();
void handle_shunk_system();
