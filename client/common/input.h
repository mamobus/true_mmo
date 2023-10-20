#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <common/game_t.h>

static camera_t* camera_o;

void move_camera_x(float x);
void move_camera_y(float y);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void setup_input(game_t* game);