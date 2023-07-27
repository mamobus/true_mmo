#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "../common/game.h"

typedef struct Game_t Game_t;

void load_level_in_GPU(Game_t* game);

void draw(Game_t* game);