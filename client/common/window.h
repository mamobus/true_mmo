#pragma once
// #ifndef window_h
// #define window_h

#include <GLFW/glfw3.h>
#include <assert.h>

typedef struct Window_t
{
    GLFWwindow* pointer;

    int width;
    int height;
} Window_t;

struct Window_t create_window();

// #endif //window_h