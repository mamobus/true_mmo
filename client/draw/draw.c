#include "draw.h"

// GLuint stride_xy = 0;
// float stride_x = 0;
// float stride_y = 0;

#define print_opengl_param(param) \
do{ \
    int _param; \
    glGetIntegerv(#param, &_param); \
    printf(#param " %u\n", _param); \
} while(0) 

void setup_draw(game_t* game)
{
    GLenum err = glewInit();

    game->map_progID = load_shaders("../assets/shaders/vertex.glsl", /*"../assets/shaders/geometry.glsl",*/ "../assets/shaders/fragment.glsl");
    game->hud_progID = load_shaders("../assets/shaders/hud_vertex.glsl", /*"../assets/shaders/geometry.glsl",*/ "../assets/shaders/hud_fragment.glsl");
    glGenVertexArrays(1, &game->VertexArrayID);
	glBindVertexArray(game->VertexArrayID);

    //there i load things that are not that hard to create extra functions for that
    game->tileset_textureID = loadTexture("../assets/tileset/spritesheet.png");
    game->uni.map_tileset  = glGetUniformLocation(game->map_progID, "my_tileset_texture");
    game->uni.hud_set      = glGetUniformLocation(game->hud_progID, "my_hud_texture");
    game->uni.camera_pos       = glGetUniformLocation(game->map_progID, "camera_pos");
    game->uni.window_size      = glGetUniformLocation(game->map_progID, "window_size");
    game->uni.point_size       = glGetUniformLocation(game->map_progID, "point_size");
    game->uni.grid_size        = glGetUniformLocation(game->map_progID, "grid_size");

    // glbindprogra


    printf("winsize %d %d\n", game->window.height, game->window.width);

    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); 
    glEnable(GL_DEPTH_CLAMP);
    // printf("before GL_DEPTH_CLAMP\n");
    // printf("after GL_DEPTH_CLAMP\n");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    
    // glEnable(GL_POLYGON_SMOOTH);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // GL_CHECK(glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL));
    


    glEnable(GL_POINT_SPRITE);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(32.0);
    glPointParameterf(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);
    
    glClearColor(0.19, 0.82, 0.69, 1.0);

    print_opengl_param(GL_MAX_TEXTURE_SIZE);
    print_opengl_param(GL_POINT_SIZE);
    // print_opengl_param(GL_MAX_TEXTURE_BUFFER_SIZE);
    // GL_MAX_TEXTURE_SIZE

    printf("setup finished\n");
}

void draw_chunk(game_t* game, int x, int y)
{
    int width  = game->chunk_manager.width;
    int height = game->chunk_manager.height;
    chunk_t chunk = game->chunk_manager.chunks[x + y*width];

    assert(chunk.vbo != 0);
    glBindBuffer(GL_ARRAY_BUFFER, chunk.vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 4*sizeof(float), 0*sizeof(float));
    glVertexAttribPointer(1, 1, GL_FLOAT, 0, 4*sizeof(float), 3*sizeof(float));
    
    glDrawArrays(GL_POINTS, 0, chunk.block_count);
}

void draw_mob_list(game_t* game, mob_list_t* mob_list)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mob_list->mob_sprite);
    glUniform1i(game->uni.map_tileset, 0);

    assert(mob_list->vbo != 0);
    glBindBuffer(GL_ARRAY_BUFFER, mob_list->vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 4*sizeof(float), 0*sizeof(float));
    glVertexAttribPointer(1, 1, GL_FLOAT, 0, 4*sizeof(float), 3*sizeof(float));
    
    glDrawArrays(GL_POINTS, 0, vector_size(mob_list->draw_mobs));
}

void draw_hud(game_t* game)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, game->hud_manager.texture);
    glUniform1i(game->uni.hud_set, 0);
    
    assert(game->hud_manager.vbo != 0);

    glBindBuffer(GL_ARRAY_BUFFER, game->hud_manager.vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, sizeof(float)*4, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, 0, sizeof(float)*4, sizeof(float)*2);
    // glBindBuffer(GL_ARRAY_BUFFER, game->hud_manager.vbo_pos);

    glDrawArrays(GL_TRIANGLES, 0, 6*vector_size(game->hud_manager.draw_data)); //each quad is two triangles

}

void draw(game_t* game)
{
    // glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glUseProgram(game->hud_progID);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // glEnable(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    hud_prepare_draw_data(game);
    draw_hud(game);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);



    // glEnable(GL_DEPTH_TEST);
    glUseProgram(game->map_progID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, game->tileset_textureID);
    glUniform1i(game->uni.map_tileset, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // printf("%2f %2f\n", game->camera.position.x, game->camera.position.y);
    // game->camera.position.z = 1.0;
    glUniform3f(game->uni.camera_pos , (float)game->camera.position.x, (float)game->camera.position.y, (float)game->camera.position.z);
    glUniform2f(game->uni.window_size, (float)game->window.height    , (float)game->window.width     );

    glUniform1f(game->uni.point_size, 64.0);
    glUniform1f(game->uni.grid_size , 11.0);

    for (int y=0; y < game->chunk_manager.height; y++)
    {
        for (int x=0; x < game->chunk_manager.width; x++)
        {
            // printf("CH_D ");
            draw_chunk(game, x, y);
        }
    }

    glUniform1f(game->uni.point_size, 128.0);
    glUniform1f(game->uni.grid_size , 7.0);

    mob_prepare_draw_data(game);
    for (int i=0; i < vector_size(game->mob_manager); i++)
    {

        draw_mob_list(game, &game->mob_manager[i]);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
} 

void terminate_draw(game_t* game)
{
    glDeleteVertexArrays(1, &game->VertexArrayID);
    free_chunk_manager(game);
}