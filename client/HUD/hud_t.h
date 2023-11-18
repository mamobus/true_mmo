#pragma once


#include <vec.h>
#include <vector.h>

#include <GL/glew.h>

typedef struct game_t game_t;

typedef struct hud_status_bars_t
{
    Vec2f pos;  //relative to the center of widget

    // int health;

} hud_status_bars_t;

typedef struct hud_draw_elem_t
{
    Vertex2 lt1, lb1, rt1;
    Vertex2 lb2, rt2, rb2;
} hud_draw_elem_t;

typedef struct hud_widget_t
{
    int (*on_mouse_click)(game_t* game, Vec2f nmouse_pos);
    void (*handle_draw)(game_t* game);

} hud_widget_t;

typedef struct hud_widget_storage_t
{
    hud_status_bars_t status_bars;
    
} hud_widget_storage_t;


//so for now buttons on widgets do not scale with windows but do scale with HUD scale. 
typedef struct hud_manager_t
{
    GLuint texture; //everything is in one texture
    GLuint vbo; //holds EVERYTHING from pos to uv of ALL the

    Vec2f scale;
    int do_widgets_stick;

    hud_widget_t* widgets;
    hud_draw_elem_t* draw_data;

    hud_widget_storage_t storage;

} hud_manager_t;
