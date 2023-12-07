#pragma once


#include <common/game_t.h>
#include <draw/load/load_texture.h>


void tm_init();

GLuint   load_texture(int type_id);
//always returns zero
GLuint unload_texture(GLuint texture);

int get_mob_texture_id(int mob_type_id);
int get_static_cosmetic_texture_id(int static_cosmetic_type_id);