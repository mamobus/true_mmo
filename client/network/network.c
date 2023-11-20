#include "network.h"

void net_create_manager(game_t* game)
{
    assert(enet_initialize() == 0);
    // enet_host_create
}

void net_destroy_manager(game_t* game)
{
    enet_deinitialize();
}

void net_update(game_t* game)
{
    // atexit()
}