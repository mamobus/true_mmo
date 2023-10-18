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
    draw->uni.camera_pos       = glGetUniformLocation(draw->programID, "camera_pos");
    draw->uni.window_size      = glGetUniformLocation(draw->programID, "window_size");
    draw->uni.point_size       = glGetUniformLocation(draw->programID, "point_size");
    draw->uni.grid_size        = glGetUniformLocation(draw->programID, "grid_size");


    printf("winsize %d %d\n", draw->window.height, draw->window.width);
    printf("winsize %d %d\n", draw->window.height, draw->window.width);


    load_chunk_manager("../assets/map/chunk_manager", "../assets/map/chunk_file", &draw->chunk_manager);
    load_all_chunks(&draw->chunk_manager);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); 
    // printf("before GL_DEPTH_CLAMP\n");
    glEnable(GL_DEPTH_CLAMP);
    // printf("after GL_DEPTH_CLAMP\n");

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

    printf("setup finished\n");


    mob_t mob = {0};
    mob.id = 12; 
    mob.state = STAND_BIT | LEFT_BIT | DOWN_BIT;
    mob.last_frame_time = 0;
    mob.pos.x = 2.0f; 
    mob.pos.y = 2.0f; 
    mob.pos.z = 5.0f;
    mob.vel.x = 0.001f; 
    mob.vel.y = 0.001f; 
    mob.vel.z = 0.001f;
    mob.tile_num = 0;
    draw->mob_manager = vector_create();
    printf("vector_size(draw->mob_manager) %d\n", vector_size(draw->mob_manager));
    print
    mob_add(mob, 644, &draw->mob_manager);

    for (int d=0; d < vector_size(draw->mob_manager); d++)
    {
        printf("%d\n", draw->mob_manager[d].mobs[0].id);
    }

    printf("mob setup finished\n");
}

void draw_chunk(draw_t* draw, int x, int y)
{
    int width  = draw->chunk_manager.width;
    int height = draw->chunk_manager.height;
    chunk_t chunk = draw->chunk_manager.chunks[x + y*width];

    assert(chunk.vbo != 0);
    glBindBuffer(GL_ARRAY_BUFFER, chunk.vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 4*sizeof(float), 0*sizeof(float));
    glVertexAttribPointer(1, 1, GL_FLOAT, 0, 4*sizeof(float), 3*sizeof(float));
    
    glDrawArrays(GL_POINTS, 0, chunk.tile_count);
}

void draw_mob_list(draw_t* draw, mob_list_t* mob_list)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mob_list->mob_sprite);
    glUniform1i(draw->uni.tileset_texture, 0);

    assert(mob_list->vbo != 0);
    glBindBuffer(GL_ARRAY_BUFFER, mob_list->vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 4*sizeof(float), 0*sizeof(float));
    glVertexAttribPointer(1, 1, GL_FLOAT, 0, 4*sizeof(float), 3*sizeof(float));
    
    glDrawArrays(GL_POINTS, 0, vector_size(mob_list->draw_mobs));
}

void draw(draw_t* draw)
{
    // glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(draw->programID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, draw->tileset_textureID);
    glUniform1i(draw->uni.tileset_texture, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // printf("%2f %2f\n", draw->camera.position.x, draw->camera.position.y);
    glUniform2f(draw->uni.camera_pos , draw->camera.position.x, draw->camera.position.y);
    glUniform2f(draw->uni.window_size, draw->window.height    , draw->window.width     );

    glUniform1f(draw->uni.point_size, 64.0);
    glUniform1f(draw->uni.grid_size , 32.0);

    for (int y=0; y < draw->chunk_manager.height; y++)
    {
        for (int x=0; x < draw->chunk_manager.width; x++)
        {
            // printf("CH_D ");
            draw_chunk(draw, x, y);
        }
    }

    glUniform1f(draw->uni.point_size, 128.0);
    glUniform1f(draw->uni.grid_size , 7.0);

    mob_prepare_draw_data(draw->mob_manager);
    for (int i=0; i < vector_size(draw->mob_manager); i++)
    {

        draw_mob_list(&draw, &draw->mob_manager[i]);
    }
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
} 

void terminate_draw(draw_t* draw)
{
    glDeleteVertexArrays(1, &draw->VertexArrayID);
    free_chunk_manager(&draw->chunk_manager);
}