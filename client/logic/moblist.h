// #define _MOB(name, id, drop_list, ...) 


// #define _MOB(id, name, drop_list, ...) 
#define arr(...) __VA_ARGS__
#define mob(type_id, name, size, ...) 

mob(0, mushroom, arr()

)

// int arr[2][2] = {{1,2}, {3, 4}};

//mobs have 8 directions, 4 states (stand, move, attack, cast)

/*
mobs have animation description like this:
stand, move, attack, cast, hurt, death

projectiles are so simple that only have one sprite



casts have animation steps like this:
start, continued, stop

effects have just animation

players have multiple body parts 
*/