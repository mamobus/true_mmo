#pragma once

#include <GLFW/glfw3.h>

typedef struct window_t
{
    GLFWwindow* pointer;

    int width;
    int height;
} window_t;