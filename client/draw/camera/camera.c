#include "camera.h"

void update_camera(game_t* game)
{
    game->camera.position = game->player.pos;
}