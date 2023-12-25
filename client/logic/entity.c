#include "entity.h"

#include "mob.c"
#include "player_e.c"
#include "effect.c"


void entity_create_manager(game_t* game)
{
    // mob_info_init();
    game->entity_manager.elist = vector_create();
    game->entity_manager.cosmetic = vector_create();
    game->entity_manager.distances_from_camera = vector_create();
}

void entity_destroy_manager(game_t* game)
{
    for(int i=0; i < vector_size(game->entity_manager.elist); i++)
    {
        
        vector_free(game->entity_manager.elist[i].draw_queue);
        vector_free(game->entity_manager.elist[i].entities);

        assert(game->entity_manager.elist[i].vbo != 0);
        glDeleteBuffers(1, &game->entity_manager.elist[i].vbo);

        // glDeleteTextures(1, &game->entity_manager.elist[i].sprite);
        unload_texture(game->entity_manager.elist[i].sprite);
    }
    for(int i=0; i < vector_size(game->entity_manager.cosmetic); i++)
    {
        
        vector_free(game->entity_manager.cosmetic[i].draw_queue);

        assert(game->entity_manager.cosmetic[i].vbo != 0);
        glDeleteBuffers(1, &game->entity_manager.cosmetic[i].vbo);

        // glDeleteTextures(1, &game->entity_manager.cosmetic[i].sprite);
        unload_texture(game->entity_manager.elist[i].sprite);
    }
    vector_free(game->entity_manager.elist);
    vector_free(game->entity_manager.cosmetic);
}

//for iternal use 
static void _create_list_with_1entity(game_t* game, int type_id, entity_t mob)
{
    entity_list_t new_mob_list = {0};
    new_mob_list.type_id = type_id;

    glGenBuffers(1, &new_mob_list.vbo);

    // new_mob_list.sprite = load_texture(game, new_mob_list.type_id+1); // so its only one but its ok
    new_mob_list.sprite = load_texture(new_mob_list.type_id); // so its only one but its ok
    // printf("loaded sprite %d\n", new_mob_list.sprite);
    //probably causes A LOT OF LAG

    new_mob_list.entities = vector_create();
    new_mob_list.draw_queue = vector_create();
    vector_add(&new_mob_list.entities, mob);
    vector_add(&game->entity_manager.elist, new_mob_list); //so we've added mob_list with new type to manager
}

//find type_id, add to the list
void entity_add(entity_t mob, int type_id, game_t* game)
{
    for(int i=0; i < vector_size(game->entity_manager.elist); i++)
    {
        if(game->entity_manager.elist[i].type_id == type_id)
        {
            //then its right mob list, just add mob to it
            vector_add(&game->entity_manager.elist[i].entities, mob);
            return;
        } 
    }
    
    //so we have not found right mob type_id, lets create list for this type_id
    _create_list_with_1entity(game, type_id, mob);
}

void entity_del(int id, int type_id, game_t* game)
{
    entity_manager_t entity_manager = game->entity_manager;

    for(int i=0; i < vector_size(entity_manager.elist); i++)
    {
        if(entity_manager.elist[i].type_id == type_id)
        {
            //then its right mob list
            for(int j=0; j < vector_size(entity_manager.elist[i].entities); j++)
            {
                if(entity_manager.elist[i].entities[j].id == id)
                {
                    //then its right mob, erasing it
                    vector_erase(&entity_manager.elist[i].entities, j, 1);

                    //if it was the last mob - remove moblist from manager (no entities to manage)
                    if(vector_size(entity_manager.elist[i].entities) == 0)
                    {
                        // glDeleteTextures(1, &entity_manager.elist[i].sprite);
                        unload_texture(entity_manager.elist[i].sprite);
                        glDeleteBuffers(1, &entity_manager.elist[i].vbo);
                        vector_erase(&entity_manager.elist, i, 1);
                    }
                    return;
                } 
            }
            return; //if mob not found - its already deleted. Or its a bug.
        } 
    }
}

void entity_set_state(entity_t* mob, int sprite_num)
{
    mob->sprite_num = sprite_num;
}

//replace with fast search
entity_t* entity_find_by_id(int id, game_t* game)
{
    entity_manager_t entity_manager = game->entity_manager;

    for(int i=0; i < vector_size(entity_manager.elist); i++)
    {
        for(int j=0; j < vector_size(entity_manager.elist[i].entities); j++)
        {
            if(entity_manager.elist[i].entities[j].id == id)
            {
                return &entity_manager.elist[i].entities[j];
            } 
        }
        return 0; //mob not found
    }
}

entity_t* entity_find(int id, int type_id, game_t* game)
{
    entity_manager_t entity_manager = game->entity_manager;

    for(int i=0; i < vector_size(entity_manager.elist); i++)
    {
        if(entity_manager.elist[i].type_id == type_id)
        {
            //then its right mob list
            for(int j=0; j < vector_size(entity_manager.elist[i].entities); j++)
            {
                if(entity_manager.elist[i].entities[j].id == id)
                {
                    return &entity_manager.elist[i].entities[j];
                } 
            }
            return NULL; //if mob not found - its already deleted. Or its a bug.
        } 
    }
    return NULL; //if list not found - its already deleted. Or its a bug.
}

int get_entity_global_type(int type_id)
{
    int global_type = 0;

         if(type_id >=0    & type_id <= 100 ) global_type=777; //iternal use
    else if(type_id > 100  & type_id <= 1000) global_type=1; //player / cosmetc
    // else if(type_id > 1000 & type_id <= 2000) global_type=2; //mob
    else if(type_id > 1000 & type_id <= 2000) global_type=2; //mob
    else if(type_id > 2000 & type_id <= 3000) global_type=3; //effect
    else if(type_id > 3000 & type_id <= 4000) global_type=4; //projectile

    return global_type;
}

void entities_prepare_for_drawing(game_t* game)
{
    entity_manager_t* entity_manager = &game->entity_manager;

    //so now ents can re-add their cosmetic for drawing if it still exists
    cosmetic_queue_clear(game);
    vector_erase(&entity_manager->distances_from_camera, 0, vector_size(entity_manager->distances_from_camera));

    for(int i=0; i < vector_size(entity_manager->elist); i++)
    {
        //clear in the list
        vector_erase(&entity_manager->elist[i].draw_queue, 0, vector_size(entity_manager->elist[i].draw_queue));

        for (int j=0; j < vector_size(entity_manager->elist[i].entities); j++)
        {
            int global_type = get_entity_global_type(entity_manager->elist[i].type_id);

            switch (global_type)
            {
            case 1:
                player_update(&entity_manager->elist[i].entities[j], game);
                player_add2draw_query(&entity_manager->elist[i].entities[j], &entity_manager->elist[i].draw_queue, game);
                break;

            case 2:
                mob_update(&entity_manager->elist[i].entities[j], game, entity_manager->elist[i].type_id);
                mob_add2draw_query(&entity_manager->elist[i].entities[j], &entity_manager->elist[i].draw_queue);
                break;

            case 3:
                mob_update(&entity_manager->elist[i].entities[j], game, entity_manager->elist[i].type_id);
                mob_add2draw_query(&entity_manager->elist[i].entities[j], &entity_manager->elist[i].draw_queue);
                break;

            default:
                break;
            }


            	vec3d ray_dir    = v3dnorm((vec3d){-0.612375, -0.612375, -0.5});
                // vec3 ray_dir = normalize(vec3(-2.8284271, -2.8284271, -3));
                vec3d camera_pos = game->camera.position;
                vec3d entity_pos = entity_manager->elist[i].entities[j].pos;

                vec3d relative_ent_pos = v3dsub(entity_pos, camera_pos);

                double distance_from_camera_plane = v3ddot(ray_dir, relative_ent_pos);

                vector_add(&entity_manager->distances_from_camera, (float) distance_from_camera_plane);
                // vec3d horizline = v3dnorm((vec3d){1,-1,0});
                // vec3d vertiline = v3dnorm(v3dcross(ray_dir, horizline));
                //they define plane of rendeting
                
                // float view_width  = 1920 / 32.0; //in block_diags
                // float view_height = 1080 / 32.0; //in blocks

                //proj = pos - ray_dir * dot(ray_dir, pos)
                // vec3d screenPojection = v3dsub(entity_pos, v3dscale(ray_dir, v3ddot(ray_dir, entity_pos)));
                // vec2d screenshift;
                // screenshift.x = v3ddot(screenPojection, horizline);
                // screenshift.y = v3ddot(screenPojection, vertiline);
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, entity_manager->elist[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, vector_size(entity_manager->elist[i].draw_queue)*sizeof(draw_entity_t), entity_manager->elist[i].draw_queue, GL_DYNAMIC_DRAW);
    }

    // printf("buffering started\n");
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, game->RT.ssbo_for_distances_from_camera);
    glBufferData(GL_SHADER_STORAGE_BUFFER, vector_size(entity_manager->distances_from_camera) * sizeof(float), entity_manager->distances_from_camera, GL_DYNAMIC_DRAW);

    for(int i=0; i < vector_size(entity_manager->cosmetic); i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, entity_manager->cosmetic[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, vector_size(entity_manager->cosmetic[i].draw_queue) * sizeof(draw_entity_t), entity_manager->cosmetic[i].draw_queue, GL_DYNAMIC_DRAW);
    }
}