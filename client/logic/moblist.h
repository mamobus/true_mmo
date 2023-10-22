// #define _MOB(name, id, drop_list, ...) 


// #define _MOB(id, name, drop_list, ...) 
#define arr(...) __VA_ARGS__
#define mob(type_id, name, drop, ...) 

mob(0, mushroom, arr()

)
/*
mobs have animation description like this:
stand, move, attack, cast, hurt, death

projectiles are so simple that only have one sprite



casts have animation steps like this:
start, continued, stop

effects have just animation

players have multiple body parts 
*/