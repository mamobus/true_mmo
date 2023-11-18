#pragma once


#include <common/game_t.h>
#include <draw/textures/texture_manager.h>
#include <iso646.h>
#include <math.h>

#include <debug_defines.h>

void hud_create_manager(game_t* game);
void hud_destroy_manager(game_t* game);

void hud_prepare_draw_data(game_t* game);

// void hud_push_widget
// void hud_pop_widget