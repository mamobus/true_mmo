#include "load_texture.h"

GLuint loadTexture(const char* filename) {
    unsigned char* image;
    unsigned int width, height;

    // Decode the PNG file and retrieve the width, height, and pixel data
    unsigned int error = lodepng_decode32_file(&image, &width, &height, filename);
    if (error != 0) {
        printf("Error decoding PNG: %s\n", lodepng_error_text(error));
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load the image data into the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Free the memory allocated for the image data
    free(image);

    return textureID;
}
