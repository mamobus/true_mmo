#pragma once

// #include <GL/glew.h>
#include "../common/game.h"
#include <string.h>
// #include "../draw/load_texture.h"
#include "cute_tiled.h"
#include <malloc.h>

char* get_tileset_path(char* map_path, char* relative_tileset_path);

void load_level(chunk_system_t* chunk_system);

void free_level(chunk_system_t* chunk_system);


