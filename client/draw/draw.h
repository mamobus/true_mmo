#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "../common/vec.h"
#include "../draw/load_shaders.h"
#include "../draw/load_texture.h"
#include "../load/chunk.h"

#include "../includes/debug_defines.h"

typedef struct uniforms_t
{
    GLuint tileset_texture;
    GLuint camera_coords;
    // GLuint textureID;
} uniforms_t;


typedef struct draw_t
{
    GLuint programID; 
    GLuint tileset_textureID;
    GLuint VertexArrayID;

    chunk_manager_t chunk_manager;
    uniforms_t uni;
} draw_t;

void init_draw(draw_t* draw);

void draw_chunk(draw_t* draw, int x, int y);

void draw(draw_t* draw);

void terminate_draw(draw_t* draw);