#include "player_movement.h"

void move_player(game_t* game, Vec2f direction)
{
    //there might be better logic but we dont care for now

    game->player.vel.x = direction.x;
    game->player.vel.y = direction.y;
    game->player.vel.z = 0;
}