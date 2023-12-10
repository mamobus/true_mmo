// #define _MOB(name, id, drop_list, ...) 


// #define ENT_CAST_BIT   0b10000000
// #define MOB_ATTACK_BIT 0b01000000
// #define MOB_MOVE_BIT   0b00100000
// #define MOB_STAND_BIT  0b00010000
// #define _MOB(id, name, drop_list, ...) 
// #define arr(...) __VA_ARGS__
// #define mob(type_id, name, texture, pixel_H, pixel_W, texture_H, texture_W, stand_frames, move_frames, attack_frames, cast_frames, death_frames, ...) 

// mob(0, black_mushroom, MOB_BLACK_MUSHROOM)
// mob(1, green_mushroom, MOB_GREEN_MUSHROOM)
// mob(2, white_mushroom, MOB_WHITE_MUSHROOM);
// mob(2, stole_girl, STOLEN_GIRL)

mob(1001, Alice, "../assets/mob_sprites/Alice.png"       , 109, 93 , 8, 8, 6, 7, 0, 0, 0)
mob(1002, Stolen, "../assets/mob_sprites/stolen_girl.png", 128, 128, 7, 7, 6, 8, 7, 0, 4)

#undef mob
// mobs have 8 directions, 4 states (stand, move, attack, cast)

/*
mobs have animation description like this:
stand, move, attack, cast, hurt, death

projectiles are so simple that only have one sprite



casts have animation steps like this:
start, continued, stop

effects have just animation

players have multiple body parts 
*/