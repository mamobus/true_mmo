#include "draw.h"


void load_level_in_GPU(Game_t* game)
{

}

void draw(Game_t* game)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, game->draw.tilesetID);
    glUniform1i(game->draw.textureID, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, game->draw.vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);   

    // glEnableVertexAttribArray(1);
    // glBindBuffer(GL_ARRAY_BUFFER, game->instance_bufer);
    // glVertexAttribPointer(1, 1, GL_INT, 0, 0, 0); 

    glDrawArraysInstanced(GL_POINTS, 0, 2, 2);

    glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);
}