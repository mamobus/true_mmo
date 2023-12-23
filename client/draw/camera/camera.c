#include "camera.h"

void update_camera(game_t* game)
{
    game->camera.shift = v3dsub(game->player.pos, game->camera.position);
    game->camera.position = game->player.pos;
}