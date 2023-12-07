#pragma once

#include "window.h"

void create_window(game_t* game)
{
    window_t window = {};

    assert(glfwInit());

    glfwWindowHint(GLFW_SAMPLES, 0); // antialiasing off, it breaks FUCKING EVERYTHING
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window.width = mode->width ;
    window.height = mode->height;

    window.pointer = glfwCreateWindow(window.width, window.height, "renderer_gl", glfwGetPrimaryMonitor(), 0);
    if(window.pointer == 0) //so 4.6 is too modern
    {  
        glfwWindowHint(GLFW_SAMPLES, 0); // antialiasing off, it breaks FUCKING EVERYTHING
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Then wee want OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

        window.pointer = glfwCreateWindow(window.width, window.height, "renderer_gl", glfwGetPrimaryMonitor(), 0);
    }
    assert(window.pointer);


    glfwMakeContextCurrent(window.pointer);

    // glfwSetInputMode(window.pointer, GLFW_STICKY_KEYS, 1);
    // glfwSetInputMode(window.pointer, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    game->window = window;
}
