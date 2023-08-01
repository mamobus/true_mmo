#pragma once

// #include <GL/glew.h>
#include "../common/game.h"
#include <string.h>
// #include "../draw/load_texture.h"
#include "../map/cute_tiled.h"
#include <malloc.h>

typedef __int128_t int_id;



char* get_tileset_path(char* map_path, char* relative_tileset_path);

void load_level(Game_t* game);

void free_level(Game_t* game);

void create_shunk_system();
void load_map_to_chunks();
void load_chunk();
void free_chunk();
void handle_shunk_system();
