#include "entity.h"

#include "mob.c"
#include "player.c"


mob_typeinfo_t mobinfo[10] = {0};
void mob_info_init()
{
    // mobinfo[3
    #define mob(type_id, name, texture, pixel_H, pixel_W, texture_H, texture_W, stand_frames, move_frames, attack_frames, cast_frames, death_frames, ...) \
    mobinfo[type_id].p##ixel_H = pixel_H; \
    mobinfo[type_id].p##ixel_W = pixel_W; \
    mobinfo[type_id].t##exture_H = texture_H; \
    mobinfo[type_id].t##exture_W = texture_W; \
    mobinfo[type_id].s##tand_frames = stand_frames; \
    mobinfo[type_id].m##ove_frames = move_frames; \
    mobinfo[type_id].a##ttack_frames = attack_frames; \
    mobinfo[type_id].c##ast_frames = cast_frames; \
    mobinfo[type_id].d##eath_frames = death_frames; \
    // printf("%d %d %d %d\n", pixel_H, texture_W, stand_frames, move_frames);
    #include <moblist.h>
}

void entity_create_manager(game_t* game)
{
    mob_info_init();
    game->entity_manager.elist = vector_create();
    game->entity_manager.cosmetic = vector_create();
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
    else if(type_id > 1000 & type_id <= 2000) global_type=3; //mob
    else if(type_id > 2000 & type_id <= 3000) global_type=4; //effect
    else if(type_id > 3000 & type_id <= 4000) global_type=5; //projectile

    return global_type;
}

void entities_prepare_for_drawing(game_t* game)
{
    entity_manager_t* entity_manager = &game->entity_manager;

    //so now ents can re-add their cosmetic for drawing if it still exists
    cosmetic_queue_clear(game);

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
                // player_add2draw_query()
                break;

            case 3:
                mob_update(&entity_manager->elist[i].entities[j], game, entity_manager->elist[i].type_id);
                mob_add2draw_query(&entity_manager->elist[i].entities[j], &entity_manager->elist[i].draw_queue);
                break;
            
            default:
                break;
            }
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, entity_manager->elist[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, vector_size(entity_manager->elist[i].draw_queue) * sizeof(draw_entity_t), entity_manager->elist[i].draw_queue, GL_DYNAMIC_DRAW);
    }

    // printf("buffering started\n");

    for(int i=0; i < vector_size(entity_manager->cosmetic); i++)
    {
        // printf("vector_size(entity_manager.cosmetic[i].draw_queue) %d\n", vector_size(entity_manager->cosmetic[i].draw_queue));
        // for(int j=0; j < vector_size(entity_manager.cosmetic[i].draw_queue); j++)
        // {
        //     draw_entity_t draw_mob = entity_manager.cosmetic[i].draw_queue[j];
            // printf("buffering %.1f %.1f %.1f %.1f\n", draw_mob.pos.x, draw_mob.pos.y, draw_mob.pos.z, draw_mob.sprite_num);
        // }
        glBindBuffer(GL_ARRAY_BUFFER, entity_manager->cosmetic[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, vector_size(entity_manager->cosmetic[i].draw_queue) * sizeof(draw_entity_t), entity_manager->cosmetic[i].draw_queue, GL_DYNAMIC_DRAW);
        //  draw_entity_t cosmetic = {1,2,3,4};
        // glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(draw_entity_t), &cosmetic, GL_DYNAMIC_DRAW);    
   // glBufferData(GL_ARRAY_BUFFER, vector_size(            cosmetic_list->draw_queue) * sizeof(draw_entity_t), cosmetic_list->draw_queue, GL_DYNAMIC_DRAW);    
    }
    // printf("buffering ended\n\n");
}