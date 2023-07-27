#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#define LODEPNG_NO_COMPILE_ZLIB
#include "lodepng.h"

GLuint loadTexture(const char* filename);