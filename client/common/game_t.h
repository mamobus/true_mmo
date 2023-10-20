#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//structs

#include <draw/camera/camera_t.h>
#include <draw/window/window_t.h>
#include <logic/mob/mob_t.h>
#include <map/chunk_t.h>

typedef struct uniforms_t
{
    GLuint map_tileset;
    GLuint camera_pos;
    GLuint window_size;
    // GLuint textureID;
    GLuint point_size;
    GLuint grid_size;
} uniforms_t;

typedef struct game_t
{
    GLuint programID; 
    GLuint tileset_textureID;
    GLuint VertexArrayID;
    uniforms_t uni;

    camera_t camera;
    window_t window;

    chunk_manager_t chunk_manager;
    mob_manager_t mob_manager;
} game_t;
