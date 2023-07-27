#include "game.h"

void give_this_game_a_window(Game_t* game)
{
    Window_t window;

    window = create_window();

    game->window = window;
}
