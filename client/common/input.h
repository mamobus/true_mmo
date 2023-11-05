#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <common/game_t.h>

extern game_t game;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void setup_input(game_t* game);