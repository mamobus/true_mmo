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
    assert(glewInit() == 0);

    game->tile_progID = load_shaders_geom("../assets/shaders/vertex.glsl", "../assets/shaders/geometry.glsl", "../assets/shaders/fragment.glsl");
    game->hud_progID = load_shaders("../assets/shaders/hud_vertex.glsl", /*"../assets/shaders/geometry.glsl",*/ "../assets/shaders/hud_fragment.glsl");
    glGenVertexArrays(1, &game->VertexArrayID);
	glBindVertexArray(game->VertexArrayID);

    //there i load things that are not that hard to create extra functions for that
    game->tileset_textureID = load_texture(TEXTURE_TILESET);
    game->uni.map_tileset = glGetUniformLocation(game->tile_progID, "my_tileset_texture");
    game->uni.hud_set     = glGetUniformLocation(game->hud_progID, "my_hud_texture");
    game->uni.camera_pos    = glGetUniformLocation(game->tile_progID, "camera_pos");
    game->uni.in_world_size = glGetUniformLocation(game->tile_progID, "in_world_size");
    game->uni.in_textr_size = glGetUniformLocation(game->tile_progID, "in_textr_size");
    // game->uni.grid_size        = glGetUniformLocation(game->tile_progID, "grid_size");

    game->scale = 4.0f;

    printf("winsize %d %d\n", game->window.height, game->window.width);

    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); 
    glEnable(GL_DEPTH_CLAMP);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    
    // glEnable(GL_POLYGON_SMOOTH);
    // glclient

    glClearColor(0.19, 0.82, 0.69, 1.0);

    // print_opengl_param(GL_MAX_TEXTURE_SIZE);
    // print_opengl_param(GL_POINT_SIZE);
    // print_opengl_param(GL_MAX_TEXTURE_BUFFER_SIZE);

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

void draw_mob_list(game_t* game, entity_list_t* mob_list)
{
    // mob_typeinfo_t thistmobinfo = mobinfo[mob_list->type_id];
    // glUniform2f(game->uni.in_world_size, (float)thistmobinfo.pixel_W/game->window.width*game->scale, (float)thistmobinfo.pixel_H/game->window.height*game->scale);
    // glUniform2f(game->uni.in_textr_size, 1.f/thistmobinfo.texture_W, 1.f/thistmobinfo.texture_H);

    glUniform2f(game->uni.in_world_size, (float)74/game->window.width*game->scale, (float)87/game->window.height*game->scale);
    glUniform2f(game->uni.in_textr_size, 1.f/10, 1.f/10);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mob_list->sprite);
    glUniform1i(game->uni.map_tileset, 0);

    assert(mob_list->vbo != 0);
    glBindBuffer(GL_ARRAY_BUFFER, mob_list->vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 4*sizeof(float), 0*sizeof(float));
    glVertexAttribPointer(1, 1, GL_FLOAT, 0, 4*sizeof(float), 3*sizeof(float));
    
    glDrawArrays(GL_POINTS, 0, vector_size(mob_list->draw_queue));
}

void draw_cosmetic_listd(game_t* game, cosmetic_list_t* cosmetic_list)
{
    // mob_typeinfo_t thistmobinfo = mobinfo[mob_list->type_id];
    // glUniform2f(game->uni.in_world_size, (float)thistmobinfo.pixel_W/game->window.width*game->scale, (float)thistmobinfo.pixel_H/game->window.height*game->scale);
    // glUniform2f(game->uni.in_textr_size, 1.f/thistmobinfo.texture_W, 1.f/thistmobinfo.texture_H);
    // printf("vbo %d sprite %d\n", cosmetic_list->vbo, cosmetic_list->sprite);
    glUniform2f(game->uni.in_world_size, (float)35/game->window.width*game->scale, (float)47/game->window.height*game->scale);
    glUniform2f(game->uni.in_textr_size, 1.f/15, 1.f/10);
// print

    glActiveTexture(GL_TEXTURE0);
    assert(cosmetic_list->sprite > 0);
    glBindTexture(GL_TEXTURE_2D, cosmetic_list->sprite);
    glUniform1i(game->uni.map_tileset, 0);
// print

    assert(cosmetic_list->vbo > 0);
    glBindBuffer(GL_ARRAY_BUFFER, cosmetic_list->vbo);
// print

    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 4*sizeof(float), 0*sizeof(float));
    glVertexAttribPointer(1, 1, GL_FLOAT, 0, 4*sizeof(float), 3*sizeof(float));
// print
    
    // printf
    assert(cosmetic_list->draw_queue > 0);
    assert(vector_size(cosmetic_list->draw_queue) > 0);

    // glBindBuffer(GL_ARRAY_BUFFER, cosmetic_list->vbo);
    // draw_entity_t cosmetic = {1,2,3,4};
    // glBufferData(GL_ARRAY_BUFFER, vector_size(cosmetic_list->draw_queue) * sizeof(draw_entity_t), cosmetic_list->draw_queue, GL_DYNAMIC_DRAW);    

    glDrawArrays(GL_POINTS, 0, vector_size(cosmetic_list->draw_queue));
// print
}

void draw_hud(game_t* game)
{
    hud_prepare_draw_data(game);

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

void draw_map(game_t* game)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, game->tileset_textureID);
    glUniform1i(game->uni.map_tileset, 0); //cause GL_TEXTURE0

    glUniform3f(game->uni.camera_pos , (float)game->camera.position.x, (float)game->camera.position.y, (float)game->camera.position.z);
    glUniform2f(game->uni.in_world_size, 64.f/game->window.width*game->scale, 64.f/game->window.height*game->scale);
    glUniform2f(game->uni.in_textr_size, 1.f/11, 1.f/11);


    for (int y=0; y < game->chunk_manager.height; y++)
    {
        for (int x=0; x < game->chunk_manager.width; x++)
        {
            // printf("CH_D ");
            draw_chunk(game, x, y);
        }
    }
}

void draw_entities(game_t* game)
{

    // get_mo
    // glUniform1f(game->uni.point_size, 128.0);
    // glUniform1f(game->uni.grid_size , 7.0);

    for (int i=0; i < vector_size(game->entity_manager.elist); i++)
    {
        // get_ty
        draw_mob_list(game, &game->entity_manager.elist[i]);
    }
    // printf("drawing vector_size(game->entity_manager.cosmetic) %d\n", vector_size(game->entity_manager.cosmetic));
    for (int i=0; i < vector_size(game->entity_manager.cosmetic); i++)
    // for (int i=0; i < vector_size(      entity_manager.cosmetic); i++)
    {
        // get_ty
        // printf("%d v%p vs%d %d %d\n", game->entity_manager.cosmetic[i].type_id, game->entity_manager.cosmetic[i].draw_queue, vector_size(game->entity_manager.cosmetic[i].draw_queue), game->entity_manager.cosmetic[i].sprite, game->entity_manager.cosmetic[i].vbo);
        // printf("t rying to draw qeue with [0] %f %f %f_%f", game->entity_manager.cosmetic[i].draw_queue[0].pos.x, game->entity_manager.cosmetic[i].draw_queue[0].pos.y, game->entity_manager.cosmetic[i].draw_queue[0].pos.z, game->entity_manager.cosmetic[i].draw_queue[0].sprite_num);
        draw_cosmetic_listd(game, &game->entity_manager.cosmetic[i]);
        // printf("cosmetic queue drawn\n");
    }
}

void draw(game_t* game)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glClear(GL_COLOR_BUFFER_BIT);
    // glBindVertexArray(game->VertexArrayID);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableClientState(GL_VERTEX_ARRAY);

    
    // glEnable(GL_DEPTH_TEST);
    // glDisable(GL_DEPTH_TEST);
    glUseProgram(game->hud_progID);
    draw_hud(game);


    // glEnable(GL_DEPTH_TEST);
    glUseProgram(game->tile_progID);
    draw_map(game);
    draw_entities(game);
    

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Sleep(1);
} 

void terminate_draw(game_t* game)
{
    glDeleteVertexArrays(1, &game->VertexArrayID);
}