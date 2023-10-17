#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
// #include "../common/vec.h"
#include "camera.h"
#include "window.h"
#include "../draw/load/load_shaders.h"
#include "../draw/load/load_texture.h"
#include "../load/chunk.h"
#include "../logic/mob.h"

#include "../includes/debug_defines.h"

typedef struct uniforms_t
{
    GLuint tileset_texture;
    GLuint camera_pos;
    GLuint window_size;
    // GLuint textureID;
} uniforms_t;


typedef struct draw_t
{
    GLuint programID; 
    GLuint tileset_textureID;
    GLuint VertexArrayID;
    uniforms_t uni;

    chunk_manager_t chunk_manager;

    camera_t camera;
    Window_t window;

    mob_manager_t mob_manager;
} draw_t;

void init_draw(draw_t* draw);

void draw_chunk(draw_t* draw, int x, int y);

void draw(draw_t* draw);

void terminate_draw(draw_t* draw);