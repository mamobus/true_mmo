#include "entity.h"
#include "cosmetic.c"
#include <math.h>


#define PI 3.14159265358979323846
int player_get_direction_bits (vec3d dir)
{
    int state = 0;

    // double x = +dir.x - dir.y / 2; //x down-right
    double x = +dir.x - dir.y / 2; //x down-right
    double y = -dir.x - dir.y / 2; //x down-left
    x = -1.0;
    y = 0.0;
    // double angle = atan2(y, x) + PI;
    double angle = atan2(y, x);
    int steps = ((int)round(angle / (PI / 4)) % 8);
    // printf("%lf, %d\n", angle, steps);
    if (steps < 0) steps += 8;

    switch (steps)
    {
    case 0:
        state = PLAYER_RIGHT_BIT;
        // printf("PLAYER_RIGHT_BIT\n");
        break;
    case 1:
        state = PLAYER_RIGHT_BIT | PLAYER_UP_BIT;
        // printf("PLAYER_RIGHT_BIT | PLAYER_UP_BIT\n");
        break;
    case 2:
        state = PLAYER_UP_BIT;
        // printf("PLAYER_UP_BIT\n");
        break;
    case 3:
        state = PLAYER_LEFT_BIT | PLAYER_UP_BIT;
        // printf("PLAYER_LEFT_BIT | PLAYER_UP_BIT\n");
        break;
    case 4:
        state = PLAYER_LEFT_BIT;
        // printf("PLAYER_LEFT_BIT\n");
        break;
    case 5:
        state = PLAYER_LEFT_BIT | PLAYER_DOWN_BIT;
        // printf("PLAYER_LEFT_BIT | PLAYER_DOWN_BIT\n");
        break;
    case 6:
        state = PLAYER_DOWN_BIT;
        // printf("PLAYER_DOWN_BIT\n");
        break;
    case 7:
        state = PLAYER_RIGHT_BIT | PLAYER_DOWN_BIT;
        // printf("PLAYER_RIGHT_BIT | PLAYER_DOWN_BIT\n");
        break;

    default:
        state = PLAYER_UP_BIT;
        break;
    }

    return state;
}

animinfo_t get_player_animinfo(int state)
{
    int shift = 0;
    int len = 0;

    int player_action = state & PLAYER_ACTION_BITMASK;
    int player_direction = state & PLAYER_DIRECTION_BITMASK;

    switch (player_action)
    {
    case PLAYER_IDLE_BIT: {
        len = 1; //in idle no animation
        if(player_direction == PLAYER_DOWN_BIT){ //only down
            shift = 0;
        } 
        else if((player_direction == PLAYER_LEFT_BIT  | PLAYER_DOWN_BIT) 
             or (player_direction == PLAYER_RIGHT_BIT | PLAYER_DOWN_BIT)){
            shift = 1;
        }
        else if((player_direction == PLAYER_LEFT_BIT) or (player_direction == PLAYER_RIGHT_BIT)){
            shift = 2;
        }
        else if((player_direction == PLAYER_UP_BIT | PLAYER_LEFT_BIT)
             or (player_direction == PLAYER_UP_BIT | PLAYER_RIGHT_BIT)){
            shift = 3;
        }
        else if(player_direction == PLAYER_UP_BIT){
            shift = 4;
        }
        else{
            printf("INCORRECT PLAYER STATE!!111\n");
            exit(721);
        }
        break;
    }
    case PLAYER_SITTING_BIT:{
        len = 1; //in sitting no animation
        if(player_direction == PLAYER_DOWN_BIT){ //only down
            shift = 5;
        } 
        else if((player_direction == PLAYER_LEFT_BIT  | PLAYER_DOWN_BIT) 
             or (player_direction == PLAYER_RIGHT_BIT | PLAYER_DOWN_BIT)){
            shift = 6;
        }
        else if((player_direction == PLAYER_LEFT_BIT) or (player_direction == PLAYER_RIGHT_BIT)){
            shift = 7;
        }
        else if((player_direction == PLAYER_UP_BIT | PLAYER_LEFT_BIT)
             or (player_direction == PLAYER_UP_BIT | PLAYER_RIGHT_BIT)){
            shift = 8;
        }
        else if(player_direction == PLAYER_UP_BIT){
            shift = 9;
        }
        else{
            printf("INCORRECT PLAYER STATE!!111\n");
            exit(722);
        }
        break;
    }
    case PLAYER_PICKUP_BIT:{
        len = 2; //2 frame anim
        if(player_direction & PLAYER_DOWN_BIT){ //only down
            shift = 10;
        } 
        else if(player_direction & PLAYER_DOWN_BIT){ //only down
            shift = 12;
        } 
        else{
            printf("INCORRECT PLAYER STATE!!111\n");
            exit(723);
        }
        break;
    }     
    case PLAYER_MOVE_BIT:
    {
        len = 8;
        if(player_direction == PLAYER_DOWN_BIT){ //only down
            shift = 14;
        } 
        else if((player_direction == (PLAYER_LEFT_BIT  | PLAYER_DOWN_BIT)) or (player_direction == (PLAYER_RIGHT_BIT | PLAYER_DOWN_BIT)))
        {
            shift = 22; printf("%X, %X, %X\n",player_direction, PLAYER_LEFT_BIT | PLAYER_DOWN_BIT, PLAYER_RIGHT_BIT | PLAYER_DOWN_BIT);
            printf("%X, %X, %X\n",player_direction == (PLAYER_LEFT_BIT | PLAYER_DOWN_BIT), player_direction == (PLAYER_RIGHT_BIT | PLAYER_DOWN_BIT), (player_direction == (PLAYER_LEFT_BIT  | PLAYER_DOWN_BIT)) or (player_direction == (PLAYER_RIGHT_BIT | PLAYER_DOWN_BIT)));
        }
        else if((player_direction == PLAYER_LEFT_BIT) or (player_direction == PLAYER_RIGHT_BIT)){
            shift = 30;
        }
        else if((player_direction == PLAYER_UP_BIT | PLAYER_LEFT_BIT)
             or (player_direction == PLAYER_UP_BIT | PLAYER_RIGHT_BIT)){
            shift = 38;
        }
        else if(player_direction == PLAYER_UP_BIT){
            shift = 46;
        }
        else{
            printf("INCORRECT PLAYER STATE!!111\n");
            exit(724);
        }
        break;
    }   
    case PLAYER_ATTACK_BIT:
    {
        len = 7;
        if(player_direction & PLAYER_DOWN_BIT){ //only down
            shift = 54;
        } 
        else if(player_direction & PLAYER_UP_BIT){ //only down
            shift = 61;
        } 
        else{
            printf("INCORRECT PLAYER STATE!!111\n");
            exit(725);
        }
        break;
    }
    case PLAYER_CAST_BIT:
    {
        len = 6;
        if(player_direction & PLAYER_DOWN_BIT){ //only down
            shift = 68;
        } 
        else if(player_direction & PLAYER_UP_BIT){ //only down
            shift = 74;
        } 
        else{
            printf("INCORRECT PLAYER STATE!!111\n");
            exit(726);
        }
        break;
    }
    case PLAYER_ACTIVE_IDLE_BIT:
    {
        len = 6;
        if((player_direction & PLAYER_DOWN_BIT) or (player_direction & PLAYER_LEFT_BIT)){ //only down
            shift = 81;
        } 
        else if((player_direction & PLAYER_UP_BIT) or (player_direction & PLAYER_RIGHT_BIT)){ //only down
            shift = 87;
        } 
        else{
            printf("INCORRECT PLAYER STATE!!111\n");
            exit(727);
        }
        break;
    }
    case PLAYER_DYING_BIT:
    {
        len = 2;
        if(player_direction & PLAYER_DOWN_BIT){ //only down
            shift = 93;
        } 
        else if(player_direction & PLAYER_UP_BIT){ //only down
            shift = 96;
        } 
        else{
            printf("INCORRECT PLAYER STATE!!111\n");
            exit(728);
        }
        break;
    }
    case PLAYER_DEAD_BIT:
    {
        len = 1;
        if(player_direction & PLAYER_DOWN_BIT){ //only down
            shift = 95;
        } 
        else if(player_direction & PLAYER_UP_BIT){ //only down
            shift = 98;
        } 
        else{
            printf("INCORRECT PLAYER STATE!!111\n");
            exit(729);
        }
        break;
    }

    default:
        printf("JACKPOT STATE BUT U CRASH!!111\n");
        exit(777);
        break;
    }

    animinfo_t info = {0};
    info.len = len;
    info.shift = shift;

    return info;
}


void player_add2draw_query(entity_t* player, draw_entity_t** draw_queue, game_t* game)
{
    //player body
    draw_entity_t draw_player = {0};
    draw_player.pos.x = player->pos.x;
    draw_player.pos.y = player->pos.y;
    draw_player.pos.z = player->pos.z;
    draw_player.sprite_num = (float) player->sprite_num;
    vector_add(draw_queue, draw_player);

    //player head
    draw_entity_t head = {0};
    int head_type = player->data.a;
    int xshift, yshift;
    // head.
    yshift = 0;
    switch (player->state & PLAYER_DIRECTION_BITMASK)
    {
    case PLAYER_DOWN_BIT:
        xshift = 0;
        break;
    case PLAYER_DOWN_BIT | PLAYER_LEFT_BIT:
        xshift = 1;
        break;
    case PLAYER_LEFT_BIT:
        xshift = 2;
        break;
    case PLAYER_LEFT_BIT | PLAYER_UP_BIT:
        xshift = 3;
        break;
    case PLAYER_UP_BIT:
        xshift = 4;
        break;
    
    default:
        xshift = 0;
        break;
    }

    head.pos.x = player->pos.x;
    head.pos.y = player->pos.y;
    head.pos.z = player->pos.z + 1.21;

    head.sprite_num = xshift;

    // cosmetic_queue_add(103, head, game);
    //add head with type of head_id and shift defined by state to queue
}

void player_update(entity_t* player, game_t* game)
{
    //interpolate movement
    player->pos = v3dadd(player->pos, v3dscale(player->vel, game->time_elapsed));

    //update current animation frametime
    double current_time = glfwGetTime();
    //do we need to update frame?
    if(current_time - player->last_frame_time > PLAYER_ANIMATION_FRAME_TIME)
    {
        //then we need to switch our animation frame
        player->last_frame_time = current_time;

        int state    = player->state;
        int sprite_num = player->sprite_num;

        animinfo_t animinfo = get_player_animinfo(state);

        int shift = animinfo.shift;
        int animlen = animinfo.len;

        printf("%d %d %d\n", shift, animlen, sprite_num);
        
        if(state & MOB_RIGHT_BIT)
        {
            sprite_num = -((abs(sprite_num) + 1) % animlen + shift);
        }
        else
        {
            // printf("STATE LEFT BIT\n");
            sprite_num = +((abs(sprite_num) + 1) % animlen + shift);
        }

        // printf("state %X\nshift:%d animlen:%d\nsprite_num: %d->%d\n", state, shift, animlen, player->sprite_num, sprite_num);
        player->sprite_num = sprite_num;
        // player->sprite_num = -22;
    }
}