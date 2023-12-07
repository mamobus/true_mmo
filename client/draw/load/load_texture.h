#pragma once

#include <stdio.h>
#include <stdlib.h>
// #include <GL/gl.h>
#define GLEW_STATIC
#include <GL/glew.h>
#define LODEPNG_NO_COMPILE_ZLIB
#include "lodepng.h"
// #include <GLFW/glfw3.h>

GLuint loadTexture(const char* filename);