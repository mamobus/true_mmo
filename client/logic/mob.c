#include "entity.h"

typedef struct mob_info_t
{
    char pixel_H, pixel_W;
    char texture_H, texture_W;
    char stand_frames, move_frames, attack_frames, cast_frames, death_frames;
} mob_info_t;

// mob_typeinfo_t mobinfo[10] = {0};
mob_info_t get_mob_info(int type)
{
    // mobinfo[3
    mob_info_t info = {0};

    switch (type)
    {

    #define mob(type_id, name, texture, pixel_H, pixel_W, texture_H, texture_W, stand_frames, move_frames, attack_frames, cast_frames, death_frames, ...) \
    case type_id: \
    { \
        info.p##ixel_H = pixel_H; \
        info.p##ixel_W = pixel_W; \
        info.t##exture_H = texture_H; \
        info.t##exture_W = texture_W; \
        info.s##tand_frames = stand_frames; \
        info.m##ove_frames = move_frames; \
        info.a##ttack_frames = attack_frames; \
        info.c##ast_frames = cast_frames; \
        info.d##eath_frames = death_frames; \
    }
    #include <_lists/moblist.h>

    default:
        break;
    }

    return info;
}

void mob_add2draw_query(entity_t* mob, draw_entity_t** draw_queue)
{
    // draw_queue
    draw_entity_t draw_mob = {0};
    draw_mob.pos.x = mob->pos.x;
    draw_mob.pos.y = mob->pos.y;
    draw_mob.pos.z = mob->pos.z;
    
    draw_mob.sprite_num = (float) mob->sprite_num;

    vector_add(draw_queue, draw_mob);
}

// int get_mob_shift(int type_id, int state)
// {
// }

// int get_mob_animlen(int type_id, int state)
// {

//     return animlen;
// }

animinfo_t get_mob_animinfo(int type, int state)
{
    int shift = 0;
    int len = 0;

    mob_info_t info = get_mob_info(type);

    // printf("type %d state%d\n", type_id, state);
    int action = state & MOB_DIRECTION_BITMASK;

    switch (action)
    {
    case MOB_STAND_BIT:
        len = info.stand_frames; 
        shift = 0;
        break;
    case MOB_MOVE_BIT:
        len = info.move_frames; 
        shift = info.stand_frames*2;
        break;
    case MOB_ATTACK_BIT:
        len = info.attack_frames; 
        shift = info.stand_frames*2 + info.move_frames*2;
        break;
    case MOB_CAST_BIT:
        len = info.cast_frames; 
        shift = info.stand_frames*2 + info.move_frames*2 + info.attack_frames*2;
        break; 

    default:
        break;
    }

    animinfo_t animinfo;
    animinfo.len = len;
    animinfo.shift = shift;

    return animinfo;
}

void mob_update(entity_t* mob, game_t* game, int type_id)
{
    //interpolate movement
    mob->pos = v3dadd(mob->pos, v3dscale(mob->vel, game->time_elapsed));

    //update current animation frametime
    double current_time = glfwGetTime();
    //do we need to update frame?
    if(current_time - mob->last_frame_time > MOB_ANIMATION_FRAME_TIME)
    {
        //then we need to switch our animation frame
        mob->last_frame_time = current_time;

        int state    = mob->state;
        int sprite_num = mob->sprite_num;

        animinfo_t animinfo = get_mob_animinfo(type_id, mob->state);
        int shift = animinfo.shift;
        int animlen = animinfo.len;

        // printf("%d %d %d\n", shift, animlen, sprite_num);
        
        if(state & MOB_LEFT_BIT)
        {
            // printf("STATE LEFT BIT\n");
            if (state & MOB_DOWN_BIT) sprite_num = +((abs(sprite_num) + 1) % animlen + shift);
            else                      sprite_num = +((abs(sprite_num) + 1) % animlen + shift+animlen);
        }
        else if(state & MOB_RIGHT_BIT)
        {
            if (state & MOB_DOWN_BIT) sprite_num = -((abs(sprite_num) + 1) % animlen + shift);
            else                      sprite_num = -((abs(sprite_num) + 1) % animlen + shift+animlen);
        }

        mob->sprite_num = sprite_num;
    }
}