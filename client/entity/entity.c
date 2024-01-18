#include "entity.h"

typedef struct physics_component{
    dvec3 pos;
    dvec3 vel;
} physics_component;

typedef struct tag_player tag_player;
typedef struct tag_npc tag_npc;
typedef struct tag_monster tag_monster;
typedef struct tag_boss tag_boss;

void entity_manager_create(game_t* game)
{
    game->entity_manager.world = ecs_init();

    ECS_COMPONENT(game->entity_manager.world, physics_component);

    
    
    ECS_TAG(game->entity_manager.world, tag_player);
    ECS_TAG(game->entity_manager.world, tag_npc);
    ECS_TAG(game->entity_manager.world, tag_monster);
    ECS_TAG(game->entity_manager.world, tag_boss);

    // ECS_COM
}
