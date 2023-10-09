#include "draw.h"


void init_draw(draw_t* draw)
{
    draw->programID = load_shaders("../client/draw/shaders/vertex.glsl", "../client/draw/shaders/geometry.glsl", "../client/draw/shaders/fragment.glsl");

    
}

void draw(draw_t* draw)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, draw->tilesetID);
    glUniform1i(draw->uni.textureID, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, draw->vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);   

    // glEnableVertexAttribArray(1);
    // glBindBuffer(GL_ARRAY_BUFFER, instance_bufer);
    // glVertexAttribPointer(1, 1, GL_INT, 0, 0, 0); 

    glDrawArraysInstanced(GL_POINTS, 0, 2, 2);

    glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);
} 