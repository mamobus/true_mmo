#include "effect.h"

void effect_create_manager(game_t* game)
{
    game->effect_manager = vector_create();
}

void effect_free_manager(game_t* game)
{
    for(int i=0; i < vector_size(game->effect_manager); i++)
    {
        
        vector_free(game->effect_manager[i].draw_effects);
        vector_free(game->effect_manager[i].effects);

        assert(game->effect_manager[i].vbo != 0);
        glDeleteBuffers(1, &game->effect_manager[i].vbo);

        glDeleteTextures(1, &game->effect_manager[i].effect_sprite);
    }
    vector_free(game->effect_manager);
}

//find type_id, add to the list
void effect_add(effect_t effect, int type_id, game_t* game)
{
    for(int i=0; i < vector_size(game->effect_manager); i++)
    {
        if(game->effect_manager[i].type_id == type_id)
        {
            //then its right effect list, just add effect to it
            vector_add(&game->effect_manager[i].effects, effect);
            return;
        } 
    }
    
    //so we have not found right effect type_id, lets create list for this type_id
    _effect_create_list_with_effect(&game->effect_manager, type_id, effect);
}

//for iternal use 
void _effect_create_list_with_effect(effect_manager_t* effect_manager, int type_id, effect_t effect)
{
    effect_list_t new_effect_list = {0};
    new_effect_list.type_id = type_id;

    glGenBuffers(1, &new_effect_list.vbo);

    // double start_time = glfwGetTime();
    // int counter = 0;

    // while (glfwGetTime() - start_time < 5.0)
    // {
    //     new_effect_list.effect_sprite = loadTexture("../assets/effect_sprites/stolen_girl.png");
    //     glDeleteTextures(1, &new_effect_list.effect_sprite);
    //     counter++;
    // }

    // printf("ms per texture loading & unloading %lf\n", 5000.0/(double)counter);

    // char effect_file_name [26] = "../assets/effect_sprites/";
    // char effect_name [3] = {};
    // sprintf(effect_name, "%d", type_id);
    // strcpy(&effect_file_name[22], effect_name);

    new_effect_list.effect_sprite = loadTexture("../assets/effect_sprites/stolen_girl.png"); // so its only one but its ok
    printf("loaded stolen_girl = %d\n", new_effect_list.effect_sprite);
    //probably causes A LOT OF LAG

    new_effect_list.effects = vector_create();
    new_effect_list.draw_effects = vector_create();
    vector_add(&new_effect_list.effects, effect);
    vector_add(effect_manager, new_effect_list); //so we've added effect_list with new type to manager
}

void effect_del(int id, int type_id, game_t* game)
{
    effect_manager_t effect_manager = game->effect_manager;

    for(int i=0; i < vector_size(effect_manager); i++)
    {
        if(effect_manager[i].type_id == type_id)
        {
            //then its right effect list
            for(int j=0; j < vector_size(effect_manager[i].effects); j++)
            {
                if(effect_manager[i].effects[j].id == id)
                {
                    //then its right effect, erasing it
                    vector_erase(&effect_manager[i].effects, j, 1);

                    //if it was the last effect - remove effectlist from manager (no effects to manage)
                    if(vector_size(effect_manager[i].effects) == 0)
                    {
                        glDeleteTextures(1, &effect_manager->effect_sprite);
                        glDeleteBuffers(1, effect_manager[i].vbo);
                        vector_erase(&effect_manager, i, 1);
                    }
                    return;
                } 
            }
            return; //if effect not found - its already deleted. Or its a bug.
        } 
    }
}

void effect_set_state(effect_t* effect, int tile_num)
{
    effect->tile_num = tile_num;
}

//replace with fast search
effect_t* effect_find_by_id(int id, game_t* game)
{
    effect_manager_t effect_manager = game->effect_manager;

    for(int i=0; i < vector_size(effect_manager); i++)
    {
        for(int j=0; j < vector_size(effect_manager[i].effects); j++)
        {
            if(effect_manager[i].effects[j].id == id)
            {
                return &effect_manager[i].effects[j];
            } 
        }
        return 0; //effect not found
    }
}

effect_t* effect_find_by_id_and_type(int id, int type_id, game_t* game)
{
    effect_manager_t effect_manager = game->effect_manager;

    for(int i=0; i < vector_size(effect_manager); i++)
    {
        if(effect_manager[i].type_id == type_id)
        {
            //then its right effect list
            for(int j=0; j < vector_size(effect_manager[i].effects); j++)
            {
                if(effect_manager[i].effects[j].id == id)
                {
                    return &effect_manager[i].effects[j];
                } 
            }
            return NULL; //if effect not found - its already deleted. Or its a bug.
        } 
    }
}

void effect_update(effect_t* effect)
{
    //interpolate movement
    effect->pos.x += effect->vel.x;
    effect->pos.y += effect->vel.y;
    effect->pos.z += effect->vel.z;

    //update current animation frame
    double current_time;
    //do we need to update frame?
    current_time = glfwGetTime();
    if(current_time - effect->last_frame_time > EFFECT_ANIMATION_FRAME_TIME)
    {
        //then we need to switch our animation frame
        effect->last_frame_time = current_time;

        int state    = effect->state;
        int tile_num = effect->tile_num;

        int shift = 0;

        if(state & EFFECT_START_BIT)
            shift = 0;
        if(state & EFFECT_GOING_BIT)
            shift = 12;
        if(state & EFFECT_END_BIT)
            shift = 18;
        
        tile_num = (tile_num + 1) % 6 + shift;

        effect->tile_num = tile_num;
    }
}

void effect_prepare_draw_data(game_t* game)
{
    effect_manager_t effect_manager = game->effect_manager;

    draw_effect_t draw_effect = {0};
    for(int i=0; i < vector_size(effect_manager); i++)
    {
        //clear in the list
        vector_erase(&effect_manager[i].draw_effects, 0, vector_size(effect_manager[i].draw_effects));
        for (int j=0; j < vector_size(effect_manager[i].effects); j++)
        {
            //fill struct for drawing as vertex


            // printf("x %f x'%f\n", effect_manager[i].effects[j].pos.x, effect_manager[i].effects[j].vel.x);
            effect_update(&effect_manager[i].effects[j]);

            draw_effect.pos      =         effect_manager[i].effects[j].pos;
            draw_effect.tile_num = (float) effect_manager[i].effects[j].tile_num;

            // printf("%.1f %.1f %.1f %.1f\n", draw_effect.pos.x, draw_effect.pos.y, draw_effect.pos.z, draw_effect.tile_num);
            
            vector_add(&effect_manager[i].draw_effects, draw_effect);
    // print
        }
        glBindBuffer(GL_ARRAY_BUFFER, effect_manager[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, vector_size(effect_manager[i].draw_effects) * sizeof(draw_effect_t), effect_manager[i].draw_effects, GL_DYNAMIC_DRAW);
    }
}