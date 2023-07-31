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

/*
load_chunk

load chunks that need to be loaded, unload not nedeed ones 

free_chunk

*/