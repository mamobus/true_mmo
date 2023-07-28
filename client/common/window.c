#pragma once

#include "window.h"

struct Window_t create_window() 
{
    struct Window_t window = {};

    assert(glfwInit());

    glfwWindowHint(GLFW_SAMPLES, 1); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window.width = mode->width;
    window.height = mode->height;

    window.pointer = glfwCreateWindow(666, 666, "renderer_gl", 0, 0);
    if(window.pointer == 0)
    {  
        glfwWindowHint(GLFW_SAMPLES, 1); // 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 4.6
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

        window.pointer = glfwCreateWindow(666, 666, "renderer_gl", 0, 0);
    }

    assert(window.pointer);

    glfwMakeContextCurrent(window.pointer);

    //disables vsync
    // glfwSwapInterval( 0 );

    glfwSetInputMode(window.pointer, GLFW_STICKY_KEYS, 1);
    // glfwSetInputMode(window.pointer, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    return window;
}
