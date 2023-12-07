#include "entity.h"

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

int get_mob_shift(int type_id, int state)
{
    int shift = 0;

    if(state & MOB_STAND_BIT)
        shift = 0;
    else if(state & MOB_MOVE_BIT)
        shift = mobinfo[type_id].stand_frames*2;
    else if(state & MOB_ATTACK_BIT)
        shift = mobinfo[type_id].stand_frames*2 + mobinfo[type_id].move_frames*2;
    else if(state & MOB_CAST_BIT)
        shift = mobinfo[type_id].stand_frames*2 + mobinfo[type_id].move_frames*2 + mobinfo[type_id].attack_frames*2;

    return shift;
}

int get_mob_animlen(int type_id, int state)
{
    int animlen = 0;

    // printf("type %d state%d\n", type_id, state);

    if(state & MOB_STAND_BIT) 
        animlen = mobinfo[type_id].stand_frames; 
    else if(state & MOB_MOVE_BIT) 
        animlen = mobinfo[type_id].move_frames; 
    else if(state & MOB_ATTACK_BIT) 
        animlen = mobinfo[type_id].attack_frames; 
    else if(state & MOB_CAST_BIT) 
        animlen = mobinfo[type_id].cast_frames; 

    return animlen;
}

void mob_add2draw_query ();

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

        int shift = get_mob_shift(type_id, mob->state);
        int animlen = get_mob_animlen(type_id, mob->state);

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