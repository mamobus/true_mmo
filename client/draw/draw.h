#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "../common/vec.h"
#include "../draw/load_shaders.h"

typedef struct uniforms_t
{
    GLuint textureID;
    GLuint camera_coords;
    // GLuint textureID;
} uniforms_t;


typedef struct draw_t
{
    GLuint programID; 
    GLuint tilesetID;
    GLuint VertexArrayID;
    GLuint vertex_buffer;
    GLuint tile_buffer;
    size_t tile_count;

    uniforms_t uni;
    
    Vec3* vertex_data;
    float* tile_data;
} draw_t;

void init_draw(draw_t* draw);

void draw(draw_t* draw);