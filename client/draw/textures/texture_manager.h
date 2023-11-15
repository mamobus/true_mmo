#pragma once


#include <common/game_t.h>
#include <draw/load/load_texture.h>


GLuint   load_texture(game_t* game, textures_e texture_enum);

//always returns zero
GLuint unload_texture(game_t* game, textures_e texture_enum);