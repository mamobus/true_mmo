#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "../common/game.h"
#include "../draw/load_shaders.h"

typedef struct Game_t Game_t;

void init_draw(Game_t* game);

void draw(Game_t* game);