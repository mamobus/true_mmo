#include "draw.h"

// GLuint stride_xy = 0;
// float stride_x = 0;
// float stride_y = 0;

void init_draw(draw_t* draw)
{
    GLenum err = glewInit();

    draw->programID = load_shaders("../client/draw/shaders/vertex.glsl", "../client/draw/shaders/geometry.glsl", "../client/draw/shaders/fragment.glsl");
    glGenVertexArrays(1, &draw->VertexArrayID);
	glBindVertexArray(draw->VertexArrayID);
    //there i load things that are not that hard to create extra functions for that
    draw->tileset_textureID = loadTexture("../assets/tileset/Sprite.png");
    draw->uni.tileset_texture  = glGetUniformLocation(draw->programID, "my_tileset_texture");
    // stride_xy = glGetUniformLocation(draw->programID, "stride_xy");
    load_chunk_manager("../assets/map/chunk_manager", "../assets/map/chunk_file", &draw->chunk_manager);
    load_all_chunks(&draw->chunk_manager);

    for (int i = 0; i < draw->chunk_manager.height*draw->chunk_manager.width; i++)
    {
        for(int j = 0; j < draw->chunk_manager.chunks[i].tile_count; j++)
        {
            printf("x%1f y%1f z%1f num%2f\n", draw->chunk_manager.chunks[i].tiles[j].x, draw->chunk_manager.chunks[i].tiles[j].y, draw->chunk_manager.chunks[i].tiles[j].z, draw->chunk_manager.chunks[i].tiles[j].tile_num);
        }
        printf("\n");
    }

    // //for debugging
    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // // glBufferData(GL_ARRAY_BUFFER, sizeof(tiles), tiles, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GEQUAL); 


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    glEnable(GL_POINT_SPRITE);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(32.0);
    glPointParameterf(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);
    
    glClearColor(0.19, 0.82, 0.69, 1.0);
}

void draw_chunk(draw_t* draw, int x, int y)
{
    int width  = draw->chunk_manager.width;
    int height = draw->chunk_manager.height;
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    chunk_t chunk = draw->chunk_manager.chunks[x + y*width];
    assert(chunk.vbo != 0);
    glBindBuffer(GL_ARRAY_BUFFER, chunk.vbo);
    //{x,y,z} per vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 4*sizeof(float), 0*sizeof(float));
    //{tile_num} per vertex

    glVertexAttribPointer(1, 1, GL_FLOAT, 0, 4*sizeof(float), 3*sizeof(float));
    // glVertexAttribPointer(1, 1, GL_FLOAT, 0, 3*sizeof(float), 3);
    
    glDrawArrays(GL_POINTS, 0, chunk.tile_count);
}

void draw(draw_t* draw)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(draw->programID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, draw->tileset_textureID);
    glUniform1i(draw->uni.tileset_texture, 0);

    // glUniform2f(stride_xy, stride_x, stride_y);
    // stride_x += 0.001;
    // stride_y += 0.001;

    for (int y=0; y < draw->chunk_manager.height; y++)
    {
        for (int x=0; x < draw->chunk_manager.width; x++)
        {
            // printf("CH_D ");
            draw_chunk(draw, x, y);
        }
    }

    // glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glVertexAttribPointer(0, 3, GL_FLOAT, 0, 16, 0);
    // glVertexAttribPointer(1, 1, GL_FLOAT, 0, 3*sizeof(float), 3*sizeof(float));
    // glVertexAttribPointer(1, 1, GL_FLOAT, 0, 3*sizeof(float), 0);
    
    // glDrawArrays(GL_POINTS, 0, sizeof(v)/16);

    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);
} 

void terminate_draw(draw_t* draw)
{
    glDeleteVertexArrays(1, &draw->VertexArrayID);
    free_chunk_manager(&draw->chunk_manager);
}