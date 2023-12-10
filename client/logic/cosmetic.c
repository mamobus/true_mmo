#include "entity.h"

void _create_cosmetic_list(int type_id, draw_entity_t cosmetic, game_t* game)
{
    cosmetic_list_t new_cosmetic_list = {0};


    glGenBuffers(1, &new_cosmetic_list.vbo);
    new_cosmetic_list.type_id = type_id;
    new_cosmetic_list.sprite = load_texture(type_id); // so its only one but its ok

    new_cosmetic_list.draw_queue = vector_create();
    assert(new_cosmetic_list.draw_queue != NULL);
    

    vector_add(&new_cosmetic_list.draw_queue, cosmetic);
    vector_add(&game->entity_manager.cosmetic, new_cosmetic_list); 

    //so we've added cosmetic list with new type to manager
}

void cosmetic_queue_add(int type_id, draw_entity_t cosmetic, game_t* game)
{
    for(int i=0; i < vector_size(game->entity_manager.cosmetic); i++)
    {
        if (game->entity_manager.cosmetic[i].type_id == type_id)
        {
            vector_add(&game->entity_manager.cosmetic[i].draw_queue, cosmetic);
            // printf("adding to list %.1f %.1f %.1f %.1f\n", cosmetic.pos.x, cosmetic.pos.y, cosmetic.pos.z, cosmetic.sprite_num);
            return;
        }
    }

    //list not found
    //lets create one
    // cosmetic_list_t new_cosmetic_list = {0};
    // glGenBuffers(1, &new_cosmetic_list.vbo);
    // new_cosmetic_list.type_id = type_id;
    // new_cosmetic_list.sprite = load_texture(type_id);
    // new_cosmetic_list.draw_queue = vector_create();
    // vector_add(&game->entity_manager.cosmetic, new_cosmetic_list);
    // cosmetic_queue_add(type_id, cosmetic, game);
    _create_cosmetic_list(type_id, cosmetic, game);
}

//called every frame before entity updates SO THEY CAN WRITE TO IT
void cosmetic_queue_clear(game_t* game)
{
    // printf("erasing started\n");
    for(int i=0; i < vector_size(game->entity_manager.cosmetic); i++)
    {
        // printf("erasing %d\n", vector_size(game->entity_manager.cosmetic[i].draw_queue));
        if(vector_size(game->entity_manager.cosmetic[i].draw_queue) != 0)
            vector_erase(&game->entity_manager.cosmetic[i].draw_queue, 0, vector_size(game->entity_manager.cosmetic[i].draw_queue));
    }
    // printf("erasing ened\n");
}