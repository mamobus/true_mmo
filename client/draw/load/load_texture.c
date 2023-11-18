#include "load_texture.h"
#include <GLFW/glfw3.h>

GLuint loadTexture(const char* filename) {
    unsigned char* image;
    unsigned int width, height;

    // double start_time = glfwGetTime();
    // int counter = 0;

    // while (glfwGetTime() - start_time < 10.0)
    // {
    //     unsigned int error = lodepng_decode32_file(&image, &width, &height, filename);
    //     counter++;
    // }
    // printf("ms per texture loading into ram %lf\n", 10000.0/(double)counter);

    // Decode the PNG file and retrieve the width, height, and pixel data
    unsigned int error = lodepng_decode32_file(&image, &width, &height, filename);
    if (error != 0) {
        printf("Error decoding PNG: %s\n", lodepng_error_text(error));
        return 0;
    }

    GLuint textureID;

    // start_time = glfwGetTime();
    // counter = 0;

    // while (glfwGetTime() - start_time < 10.0)
    // {
    //     glGenTextures(1, &textureID);

    //     glBindTexture(GL_TEXTURE_2D, textureID);

    //     // Set texture parameters
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    //     glDeleteTextures(1, &textureID);
    //     counter++;
    // }
    // printf("ms per texture loading & unloading without decoding %lf\n", 10000.0/(double)counter);

    
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
    ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    // Load the image data into the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Free the memory allocated for the image data
    free(image);

    return textureID;
}
