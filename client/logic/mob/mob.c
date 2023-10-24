#include "mob.h"

void mob_create_manager(game_t* game)
{
    game->mob_manager = vector_create();
}

void mob_free_manager(game_t* game)
{
    for(int i=0; i < vector_size(game->mob_manager); i++)
    {
        
        vector_free(game->mob_manager[i].draw_mobs);
        vector_free(game->mob_manager[i].mobs);

        assert(game->mob_manager[i].vbo != 0);
        glDeleteBuffers(1, &game->mob_manager[i].vbo);

        glDeleteTextures(1, &game->mob_manager[i].mob_sprite);
    }
    vector_free(game->mob_manager);
}

//find type_id, add to the list
void mob_add(mob_t mob, int type_id, game_t* game)
{
    for(int i=0; i < vector_size(game->mob_manager); i++)
    {
        if(game->mob_manager[i].type_id == type_id)
        {
            //then its right mob list, just add mob to it
            vector_add(&game->mob_manager[i].mobs, mob);
            return;
        } 
    }
    
    //so we have not found right mob type_id, lets create list for this type_id
    _mob_create_list_with_mob(&game->mob_manager, type_id, mob);
}

//for iternal use 
void _mob_create_list_with_mob(mob_manager_t* mob_manager, int type_id, mob_t mob)
{
    mob_list_t new_mob_list = {0};
    new_mob_list.type_id = type_id;

    glGenBuffers(1, &new_mob_list.vbo);

    double start_time = glfwGetTime();
    int counter = 0;

    // while (glfwGetTime() - start_time < 5.0)
    // {
    //     new_mob_list.mob_sprite = loadTexture("../assets/mob_sprites/stolen_girl.png");
    //     glDeleteTextures(1, &new_mob_list.mob_sprite);
    //     counter++;
    // }

    printf("ms per texture loading & unloading %lf\n", 5000.0/(double)counter);

    new_mob_list.mob_sprite = loadTexture("../assets/mob_sprites/stolen_girl.png"); // so its only one but its ok
    printf("loaded stolen_girl = %d\n", new_mob_list.mob_sprite);
    //probably causes A LOT OF LAG

    new_mob_list.mobs = vector_create();
    new_mob_list.draw_mobs = vector_create();
    vector_add(&new_mob_list.mobs, mob);
    vector_add(mob_manager, new_mob_list); //so we've added mob_list with new type to manager
}

void mob_del(int id, int type_id, game_t* game)
{
    mob_manager_t mob_manager = game->mob_manager;

    for(int i=0; i < vector_size(mob_manager); i++)
    {
        if(mob_manager[i].type_id == type_id)
        {
            //then its right mob list
            for(int j=0; j < vector_size(mob_manager[i].mobs); j++)
            {
                if(mob_manager[i].mobs[j].id == id)
                {
                    //then its right mob, erasing it
                    vector_erase(&mob_manager[i].mobs, j, 1);

                    //if it was the last mob - remove moblist from manager (no mobs to manage)
                    if(vector_size(mob_manager[i].mobs) == 0)
                    {
                        glDeleteTextures(1, &mob_manager->mob_sprite);
                        glDeleteBuffers(1, mob_manager[i].vbo);
                        vector_erase(&mob_manager, i, 1);
                    }
                    return;
                } 
            }
            return; //if mob not found - its already deleted. Or its a bug.
        } 
    }
}

void mob_set_state(mob_t* mob, int tile_num)
{
    mob->tile_num = tile_num;
}

//replace with fast search
mob_t* mob_find_by_id(int id, game_t* game)
{
    mob_manager_t mob_manager = game->mob_manager;

    for(int i=0; i < vector_size(mob_manager); i++)
    {
        for(int j=0; j < vector_size(mob_manager[i].mobs); j++)
        {
            if(mob_manager[i].mobs[j].id == id)
            {
                return &mob_manager[i].mobs[j];
            } 
        }
        return 0; //mob not found
    }
}

mob_t* mob_find_by_id_and_type(int id, int type_id, game_t* game)
{
    mob_manager_t mob_manager = game->mob_manager;

    for(int i=0; i < vector_size(mob_manager); i++)
    {
        if(mob_manager[i].type_id == type_id)
        {
            //then its right mob list
            for(int j=0; j < vector_size(mob_manager[i].mobs); j++)
            {
                if(mob_manager[i].mobs[j].id == id)
                {
                    return &mob_manager[i].mobs[j];
                } 
            }
            return NULL; //if mob not found - its already deleted. Or its a bug.
        } 
    }
}

void mob_update(mob_t* mob)
{
    //interpolate movement
    mob->pos.x += mob->vel.x;
    mob->pos.y += mob->vel.y;
    mob->pos.z += mob->vel.z;

    //update current animation frame
    double current_time;
    //do we need to update frame?
    current_time = glfwGetTime();
    if(current_time - mob->last_frame_time > ANIMATION_FRAME_TIME)
    {
        //then we need to switch our animation frame
        mob->last_frame_time = current_time;

        int state    = mob->state;
        int tile_num = mob->tile_num;
        
        if(state & STAND_BIT)
        {
            //if already standing animation, move it
            //otherwise start it. Might be not from start tho should work perfectly
            if(state & LEFT_BIT)
            {
                // printf("STATE LEFT BIT\n");
                if (state & DOWN_BIT) tile_num = +((abs(tile_num) + 1) % 6);
                else                  tile_num = +((abs(tile_num) + 1) % 6 + 6);
            }
            if(state & RIGHT_BIT)
            {
                if (state & DOWN_BIT) tile_num = -((abs(tile_num) + 1) % 6);
                else                  tile_num = -((abs(tile_num) + 1) % 6 + 6);
            }
        }
        mob->tile_num = tile_num;
    }
}

void mob_prepare_draw_data(game_t* game)
{
    mob_manager_t mob_manager = game->mob_manager;

    draw_mob_t draw_mob = {0};
    for(int i=0; i < vector_size(mob_manager); i++)
    {
        //clear in the list
        vector_erase(&mob_manager[i].draw_mobs, 0, vector_size(mob_manager[i].draw_mobs));
        for (int j=0; j < vector_size(mob_manager[i].mobs); j++)
        {
            //fill struct for drawing as vertex


            // printf("x %f x'%f\n", mob_manager[i].mobs[j].pos.x, mob_manager[i].mobs[j].vel.x);
            mob_update(&mob_manager[i].mobs[j]);

            draw_mob.pos      =         mob_manager[i].mobs[j].pos;
            draw_mob.tile_num = (float) mob_manager[i].mobs[j].tile_num;

            // printf("%.1f %.1f %.1f %.1f\n", draw_mob.pos.x, draw_mob.pos.y, draw_mob.pos.z, draw_mob.tile_num);
            
            vector_add(&mob_manager[i].draw_mobs, draw_mob);
    // print
        }
        glBindBuffer(GL_ARRAY_BUFFER, mob_manager[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, vector_size(mob_manager[i].draw_mobs) * sizeof(draw_mob_t), mob_manager[i].draw_mobs, GL_DYNAMIC_DRAW);
    }
}