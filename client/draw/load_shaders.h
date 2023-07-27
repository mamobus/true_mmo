#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GLEW_STATIC
#include <GL/glew.h>

char* get_shader_code(const char* file_name);

void compile_and_check(GLuint shader_id, const char* shader_code);

//binds the programID automatically
GLuint load_shaders(const char * vertex_file_path, const char * fragment_file_path);