#include "entity.h"

typedef struct effect_info_t
{
    char pixel_H, pixel_W;
    char texture_H, texture_W;
    char start_frames, going_frames, ending_frames;
} effect_info_t;

// effect_typeinfo_t effectinfo[10] = {0};
effect_info_t get_effect_info(int type)
{
    // effectinfo[3
    effect_info_t info = {0};

    switch (type)
    {

    #define effect(type_id, name, texture, pixel_H, pixel_W, texture_H, texture_W, start_frames, going_frames, ending_frames, ...) \
    case type_id: \
    { \
        info.p##ixel_H = pixel_H; \
        info.p##ixel_W = pixel_W; \
        info.t##exture_H = texture_H; \
        info.t##exture_W = texture_W; \
        info.s##tart_frames = start_frames; \
        info.g##oing_frames = going_frames; \
        info.e##nding_frames = ending_frames; \
    }
    #include <_lists/effectlist.h>

    default:
        break;
    }

    return info;
}

void effect_add2draw_query(entity_t* effect, draw_entity_t** draw_queue)
{
    // draw_queue
    draw_entity_t draw_effect = {0};
    draw_effect.pos.x = effect->pos.x;
    draw_effect.pos.y = effect->pos.y;
    draw_effect.pos.z = effect->pos.z;
    
    draw_effect.sprite_num = (float) effect->sprite_num;

    vector_add(draw_queue, draw_effect);
}

// int get_effect_shift(int type_id, int state)
// {
// }

// int get_effect_animlen(int type_id, int state)
// {

//     return animlen;
// }

animinfo_t get_effect_animinfo(int type, int state)
{
    int shift = 0;
    int len = 0;

    effect_info_t info = get_effect_info(type);

    switch (state)
    {
    case EFFECT_START_BIT:
        len = info.start_frames; 
        shift = 0;
        break;
    case EFFECT_GOING_BIT:
        len = info.going_frames; 
        shift = info.start_frames*2;
        break;
    case EFFECT_ENDIN_BIT:
        len = info.ending_frames; 
        shift = info.start_frames*2 + info.going_frames*2;
        break;

    default:
        break;
    }

    animinfo_t animinfo;
    animinfo.len = len;
    animinfo.shift = shift;

    return animinfo;
}

void effect_update(entity_t* effect, game_t* game, int type_id)
{
    //interpolate movement
    effect->pos = v3dadd(effect->pos, v3dscale(effect->vel, game->time_elapsed));

    //update current animation frametime
    double current_time = glfwGetTime();
    // effect->data[0]

    //do we need to update frame?
    if(current_time - effect->last_frame_time > EFFECT_ANIMATION_FRAME_TIME)
    {
        //then we need to switch our animation frame
        effect->last_frame_time = current_time;

        int state    = effect->state;
        int sprite_num = effect->sprite_num;

        animinfo_t animinfo = get_effect_animinfo(type_id, effect->state);
        int shift = animinfo.shift;
        int animlen = animinfo.len;

        // printf("%d %d %d\n", shift, animlen, sprite_num);
        
        sprite_num = +((abs(sprite_num) + 1) % animlen + shift);
        
        // if(state & EFFECT_LEFT_BIT)
        // {
        //     // printf("STATE LEFT BIT\n");
        //     if (state & EFFECT_DOWN_BIT) sprite_num = +((abs(sprite_num) + 1) % animlen + shift);
        //     else                      sprite_num = +((abs(sprite_num) + 1) % animlen + shift+animlen);
        // }
        // else if(state & EFFECT_RIGHT_BIT)
        // {
        //     if (state & EFFECT_DOWN_BIT) sprite_num = -((abs(sprite_num) + 1) % animlen + shift);
        //     else                      sprite_num = -((abs(sprite_num) + 1) % animlen + shift+animlen);
        // }

        effect->sprite_num = sprite_num;
    }
}