#include "mob.h"

//find type_id, add to the list
void mob_add(mob_t mob, int type_id, mob_manager_t mob_manager)
{
    for(int i=0; i < cvector_size(mob_manager); i++)
    {
        if(mob_manager[i].type_id == type_id)
        {
            //then its right mob list, just add mob to it
            cvector_push_back(mob_manager[i].mobs, mob);
            return;
        } 
    }
    //so we have not found right mob type_id, lets create list for this type_id
    mob_list_t new_mob_list = {};

    //allocate vbo bufer
    glGenBuffers(1, &new_mob_list.vbo);

    new_mob_list.type_id = type_id;
    cvector_push_back(new_mob_list.mobs, mob);
    cvector_push_back(mob_manager, new_mob_list); //so we've added mob_list with new type to manager
}

void mob_del(int id, int type_id, mob_manager_t mob_manager)
{
    for(int i=0; i < cvector_size(mob_manager); i++)
    {
        if(mob_manager[i].type_id == type_id)
        {
            //then its right mob list
            for(int j=0; j < cvector_size(mob_manager[i].mobs); j++)
            {
                if(mob_manager[i].mobs[j].id == id)
                {
                    //then its right mob, erasing it
                    cvector_erase(mob_manager[i].mobs, j);

                    //if it was the last mob - remove moblist from manager (no mobs to manage)
                    if(cvector_size(mob_manager[i].mobs) == 0)
                    {
                        glDeleteBuffers(1, mob_manager[i].vbo);
                        cvector_erase(mob_manager, i);
                    }
                    return;
                } 
            }
            return; //if mob not found - its already deleted. Or its a bug.
        } 
    }
}

void mob_set_state(mob_t* mob, int state)
{
    mob->state = state;
}

mob_t* mob_find_by_id(int id, mob_manager_t mob_manager)
{
    for(int i=0; i < cvector_size(mob_manager); i++)
    {
        for(int j=0; j < cvector_size(mob_manager[i].mobs); j++)
        {
            if(mob_manager[i].mobs[j].id == id)
            {
                return &mob_manager[i].mobs[j];
            } 
        }
        return 0; //mob not found
    }
}

mob_t* mob_find_by_id_and_type(int id, int type_id, mob_manager_t mob_manager)
{
    for(int i=0; i < cvector_size(mob_manager); i++)
    {
        if(mob_manager[i].type_id == type_id)
        {
            //then its right mob list
            for(int j=0; j < cvector_size(mob_manager[i].mobs); j++)
            {
                if(mob_manager[i].mobs[j].id == id)
                {
                    return &mob_manager[i].mobs[j];
                } 
            }
            return NULL; //if mob not found - its already deleted. Or its a bug.
        } 
    }
}

void mob_prepare_draw_data(mob_manager_t mob_manager)
{
    draw_mob_t draw_mob;
    for(int i=0; i < cvector_size(mob_manager); i++)
    {
        //clear in the list
        cvector_clear(mob_manager[i].draw_mobs);
        for (int j=0; j < cvector_size(mob_manager[i].mobs); j++)
        {
            //fill struct for drawing as vertex
            draw_mob.pos   =        mob_manager[i].mobs[j].pos;
            draw_mob.state = (float)mob_manager[i].mobs[j].state;

            cvector_push_back(mob_manager[i].draw_mobs, draw_mob);
        }
        glBindBuffer(GL_ARRAY_BUFFER, mob_manager[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, cvector_size(mob_manager[i].draw_mobs) * sizeof(draw_mob_t), mob_manager[i].draw_mobs, GL_STATIC_DRAW);
    }
}