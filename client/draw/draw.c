#include "draw.h"

#define print printf("line %d\n", __LINE__);

void init_draw(draw_t* draw)
{
    print
    draw->programID = load_shaders("../client/draw/shaders/vertex.glsl", "../client/draw/shaders/geometry.glsl", "../client/draw/shaders/fragment.glsl");
    print
    glGenVertexArrays(1, &draw->VertexArrayID);
    print
	glBindVertexArray(draw->VertexArrayID);
    //there i load things that are not that hard to create extra functions for that
    print
    draw->tileset_textureID = loadTexture("../assets/tileset/Sprite.png");
    print
    draw->uni.tileset_texture  = glGetUniformLocation(draw->programID, "my_tileset_texture");
    print
    load_chunk_manager("../assets/chunk_manager", "../assets/chunk_file", &draw->chunk_manager);
    print
    load_all_chunks(&draw->chunk_manager);

    print
    glEnable(GL_POINT_SPRITE);
    print
    glPointParameterf(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);
}

void draw_chunk(draw_t* draw, int x, int y)
{
    int width  = draw->chunk_manager.width;
    int height = draw->chunk_manager.height;
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, draw->chunk_manager.chunks[x + y*width].vbo);
    //{x,y,z} per vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 1, 0);
    //{tile_num} per vertex
    glVertexAttribPointer(1, 1, GL_FLOAT, 0, 3, 3*sizeof(float));
    
    glDrawArrays(GL_POINTS, 0, draw->chunk_manager.chunks[x + y*width].tile_count);
}

void draw(draw_t* draw)
{
    glUseProgram(draw->programID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, draw->tileset_textureID);
    glUniform1i(draw->uni.tileset_texture, 0);

    for (int y=0; y < draw->chunk_manager.height; y++)
    {
        for (int x=0; x < draw->chunk_manager.width; x++)
        {
            draw_chunk(draw, x, y);
        }
    }
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
} 

void terminate_draw(draw_t* draw)
{
    glDeleteVertexArrays(1, &draw->VertexArrayID);
    free_chunk_manager(&draw->chunk_manager);
}