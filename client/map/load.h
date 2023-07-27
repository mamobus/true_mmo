#pragma once

#include <stdint.h>
#include <GL/glew.h>
#include "../common/game.h"
#include "../draw/load_texture.h"
#include "../map/cute_tiled.h"
#include "../draw/load_shaders.h"
#include "../common/vec.h"
#include <malloc.h>

typedef __int128_t int_id;

typedef struct level_t
{
    cute_tiled_map_t* map;
    cute_tiled_tileset_t* tileset;
} level_t;

void load_level(Game_t* game);

void free_level(Game_t* game);