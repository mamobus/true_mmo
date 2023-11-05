#include "projectile.h"

void projectile_create_manager(game_t* game)
{
    game->projectile_manager = vector_create();
}

void projectile_free_manager(game_t* game)
{
    for(int i=0; i < vector_size(game->projectile_manager); i++)
    {
        
        vector_free(game->projectile_manager[i].draw_projectiles);
        vector_free(game->projectile_manager[i].projectiles);

        assert(game->projectile_manager[i].vbo != 0);
        glDeleteBuffers(1, &game->projectile_manager[i].vbo);

        glDeleteTextures(1, &game->projectile_manager[i].projectile_sprite);
    }
    vector_free(game->projectile_manager);
}

//find type_id, add to the list
void projectile_add(projectile_t projectile, int type_id, game_t* game)
{
    for(int i=0; i < vector_size(game->projectile_manager); i++)
    {
        if(game->projectile_manager[i].type_id == type_id)
        {
            //then its right projectile list, just add projectile to it
            vector_add(&game->projectile_manager[i].projectiles, projectile);
            return;
        } 
    }
    
    //so we have not found right projectile type_id, lets create list for this type_id
    _projectile_create_list_with_projectile(&game->projectile_manager, type_id, projectile);
}

//for iternal use 
void _projectile_create_list_with_projectile(projectile_manager_t* projectile_manager, int type_id, projectile_t projectile)
{
    projectile_list_t new_projectile_list = {0};
    new_projectile_list.type_id = type_id;

    glGenBuffers(1, &new_projectile_list.vbo);

    // double start_time = glfwGetTime();
    // int counter = 0;

    // while (glfwGetTime() - start_time < 5.0)
    // {
    //     new_projectile_list.projectile_sprite = loadTexture("../assets/projectile_sprites/stolen_girl.png");
    //     glDeleteTextures(1, &new_projectile_list.projectile_sprite);
    //     counter++;
    // }

    // printf("ms per texture loading & unloading %lf\n", 5000.0/(double)counter);

    new_projectile_list.projectile_sprite = loadTexture("../assets/projectile_sprites/stolen_girl.png"); // so its only one but its ok
    printf("loaded stolen_girl = %d\n", new_projectile_list.projectile_sprite);
    //probably causes A LOT OF LAG

    new_projectile_list.projectiles = vector_create();
    new_projectile_list.draw_projectiles = vector_create();
    vector_add(&new_projectile_list.projectiles, projectile);
    vector_add(projectile_manager, new_projectile_list); //so we've added projectile_list with new type to manager
}

void projectile_del(int id, int type_id, game_t* game)
{
    projectile_manager_t projectile_manager = game->projectile_manager;

    for(int i=0; i < vector_size(projectile_manager); i++)
    {
        if(projectile_manager[i].type_id == type_id)
        {
            //then its right projectile list
            for(int j=0; j < vector_size(projectile_manager[i].projectiles); j++)
            {
                if(projectile_manager[i].projectiles[j].id == id)
                {
                    //then its right projectile, erasing it
                    vector_erase(&projectile_manager[i].projectiles, j, 1);

                    //if it was the last projectile - remove projectilelist from manager (no projectiles to manage)
                    if(vector_size(projectile_manager[i].projectiles) == 0)
                    {
                        glDeleteTextures(1, &projectile_manager->projectile_sprite);
                        glDeleteBuffers(1, projectile_manager[i].vbo);
                        vector_erase(&projectile_manager, i, 1);
                    }
                    return;
                } 
            }
            return; //if projectile not found - its already deleted. Or its a bug.
        } 
    }
}

void projectile_set_state(projectile_t* projectile, int tile_num)
{
    projectile->tile_num = tile_num;
}

//replace with fast search
projectile_t* projectile_find_by_id(int id, game_t* game)
{
    projectile_manager_t projectile_manager = game->projectile_manager;

    for(int i=0; i < vector_size(projectile_manager); i++)
    {
        for(int j=0; j < vector_size(projectile_manager[i].projectiles); j++)
        {
            if(projectile_manager[i].projectiles[j].id == id)
            {
                return &projectile_manager[i].projectiles[j];
            } 
        }
        return 0; //projectile not found
    }
}

projectile_t* projectile_find_by_id_and_type(int id, int type_id, game_t* game)
{
    projectile_manager_t projectile_manager = game->projectile_manager;

    for(int i=0; i < vector_size(projectile_manager); i++)
    {
        if(projectile_manager[i].type_id == type_id)
        {
            //then its right projectile list
            for(int j=0; j < vector_size(projectile_manager[i].projectiles); j++)
            {
                if(projectile_manager[i].projectiles[j].id == id)
                {
                    return &projectile_manager[i].projectiles[j];
                } 
            }
            return NULL; //if projectile not found - its already deleted. Or its a bug.
        } 
    }
}

void projectile_update(projectile_t* projectile)
{
    //interpolate movement
    projectile->pos.x += projectile->vel.x;
    projectile->pos.y += projectile->vel.y;
    projectile->pos.z += projectile->vel.z;

    //update current animation frame
    double current_time;
    //do we need to update frame?
    current_time = glfwGetTime();
    if(current_time - projectile->last_frame_time > PROJECTILE_ANIMATION_FRAME_TIME)
    {
        //then we need to switch our animation frame
        projectile->last_frame_time = current_time;

        int state    = projectile->state;
        int tile_num = projectile->tile_num;
        

            if(state & PROJECTILE_LEFT_BIT)
            {
                // printf("STATE LEFT BIT\n");
                if (state & PROJECTILE_DOWN_BIT) tile_num = +((abs(tile_num) + 1) % 6);
                else                  tile_num = +((abs(tile_num) + 1) % 6 + 6);
            }
            if(state & PROJECTILE_RIGHT_BIT)
            {
                if (state & PROJECTILE_DOWN_BIT) tile_num = -((abs(tile_num) + 1) % 6);
                else                  tile_num = -((abs(tile_num) + 1) % 6 + 6);
            }
        projectile->tile_num = tile_num;
    }
}

void projectile_prepare_draw_data(game_t* game)
{
    projectile_manager_t projectile_manager = game->projectile_manager;

    draw_projectile_t draw_projectile = {0};
    for(int i=0; i < vector_size(projectile_manager); i++)
    {
        //clear in the list
        vector_erase(&projectile_manager[i].draw_projectiles, 0, vector_size(projectile_manager[i].draw_projectiles));
        for (int j=0; j < vector_size(projectile_manager[i].projectiles); j++)
        {
            //fill struct for drawing as vertex


            // printf("x %f x'%f\n", projectile_manager[i].projectiles[j].pos.x, projectile_manager[i].projectiles[j].vel.x);
            projectile_update(&projectile_manager[i].projectiles[j]);

            draw_projectile.pos      =         projectile_manager[i].projectiles[j].pos;
            draw_projectile.tile_num = (float) projectile_manager[i].projectiles[j].tile_num;

            // printf("%.1f %.1f %.1f %.1f\n", draw_projectile.pos.x, draw_projectile.pos.y, draw_projectile.pos.z, draw_projectile.tile_num);
            
            vector_add(&projectile_manager[i].draw_projectiles, draw_projectile);
    // print
        }
        glBindBuffer(GL_ARRAY_BUFFER, projectile_manager[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, vector_size(projectile_manager[i].draw_projectiles) * sizeof(draw_projectile_t), projectile_manager[i].draw_projectiles, GL_DYNAMIC_DRAW);
    }
}