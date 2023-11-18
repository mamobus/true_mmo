#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <debug_defines.h>

//std libs
#include <malloc.h>
#include <stdio.h>
#include <assert.h>

//structs
#include <common/game_t.h>

//reads manager from file
void load_chunk_manager(char* manager_file_name, char* chunk_file_name, game_t* game);

void chunk_destroy_manager(game_t* game);

//also loads to VBO
// void load_chunk(game_t* game, int x, int y);

// //with deleting VBO
// void free_chunk(game_t* game, int x, int y);

void load_all_chunks(game_t* game);

void free_all_chunks(game_t* game);