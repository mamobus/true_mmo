#pragma once

#include <vec.h>
/*
what do i need?

check if collide

find entities / blocks in collider

for given player, find where it will be in next frame (time)
which is like trying to move Xf blocks and stop on hit

only block collider for now

gravity handler

maybe block properties as "slippery" / "bounciness"

*/
#include <common/game_t.h>

int gjk_separate ();