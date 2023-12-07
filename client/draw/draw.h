#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
// #include "../common/vec.h"
#include <draw/camera/camera.h>
#include <draw/window/window.h>
#include <draw/load/load_shaders.h>
// #include <draw/load/load_texture.h>
#include <draw/textures/texture_manager.h>
#include <map/chunk.h>
#include <logic/entity.h>
#include <HUD/hud.h>

#include <debug_defines.h>

#include <common/game_t.h>

void setup_draw(game_t* game);
void draw(game_t* game);
void terminate_draw(game_t* game);