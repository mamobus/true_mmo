#include "camera.h"

void update_camera(game_t* game)
{
    vec3d new_camera_pos = v3dadd(game->player.pos, v3dscale((vec3d){0.612375, 0.612375, 0.5}, 30.00));
    // vec3d new_camera_pos = game->player.pos; -0.612375, -0.612375, -0.5
    game->camera.shift = v3dsub(new_camera_pos, game->camera.position);
    game->camera.position = new_camera_pos;
}