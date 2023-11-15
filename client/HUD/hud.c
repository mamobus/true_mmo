#include "hud.h"

void push_status_bars_widget(game_t* game);

void hud_create_manager(game_t* game)
{
    game->hud_manager.do_widgets_stick = 1;

    game->hud_manager.texture = load_texture(game, HUD_TEXTURE);
    glGenBuffers(1, &game->hud_manager.vbo);
    // glGenBuffers(1, &game->hud_manager.vbo_pos);
    // glGenBuffers(1, &game->hud_manager.vbo_uvs);
    
    // game->hud_manager.scale = (Vec2d){1.0, 1.0};

    game->hud_manager.widgets = vector_create();
    game->hud_manager.draw_data = vector_create();
    // game->hud_manager. = vector_create();

    // base_HUD.
    push_status_bars_widget(game);
}

void hud_destroy_manager(game_t* game)
{   
    //free all vectors inside each widget
    // for(int i=0; i < vector_size(game->hud_manager.widgets); i++)
    // {
    //     if(game->hud_manager.widgets[i].buttons != NULL)
    //     {
    //         vector_free(game->hud_manager.widgets[i].buttons);
    //     }
    // }

    //free vector of widgets
    vector_free(game->hud_manager.widgets);
    vector_free(game->hud_manager.draw_data);
    // vector_free(game->hud_manager.);
}

void hud_prepare_draw_data(game_t* game)
{
    //clean the vector
    vector_erase(&game->hud_manager.draw_data, 0, vector_size(game->hud_manager.draw_data));

    for(int i=0; i < vector_size(game->hud_manager.widgets); i++)
    {
        //push all the hud squares to hud_m vbo
        game->hud_manager.widgets[i].handle_draw(game);
        // game->hud_manager.widgets[i].on_mouse_click(game);
    }

    // for(int i=0; i < vector_size(game->hud_manager.draw_data); i++)
    // {
    //     hud_draw_elem_t elem = game->hud_manager.draw_data[i];

    //     Vertex2* verts = &elem;

    //     for(int j=0; j < 4; j++)
    //     {
    //         printf("pos %f %f\nuv %f %f\n\n", verts[j].pos.x, verts[j].pos.y, verts[j].uv.x, verts[j].uv.y);
    //     }
    // }


    glBindBuffer(GL_ARRAY_BUFFER, game->hud_manager.vbo);
    glBufferData(GL_ARRAY_BUFFER, vector_size(game->hud_manager.draw_data) * sizeof(hud_draw_elem_t), game->hud_manager.draw_data, GL_DYNAMIC_DRAW);
}

void push_widget(game_t* game, hud_widget_t widget)
{
    vector_add(&game->hud_manager.widgets, widget);
}

hud_draw_elem_t create_rect(Vec2f center, Vec2f size, Vec2f uv_topleft, Vec2f uv_bottomright)
{
    hud_draw_elem_t elem = {0};

    elem.lt1.pos.x = center.x - size.x / 2;
    elem.lt1.pos.y = center.y + size.y / 2;
    elem.lt1.uv = uv_topleft;

    elem.lb1.pos.x = center.x - size.x / 2;
    elem.lb1.pos.y = center.y - size.y / 2;
    // elem.lb1.uv = (Vec2f){uv_topleft.x, uv_bottomright.y};
    elem.lb1.uv.x = uv_topleft.x;
    elem.lb1.uv.y = uv_bottomright.y;

    elem.rt1.pos.x = center.x + size.x / 2;
    elem.rt1.pos.y = center.y + size.y / 2;
    // elem.rt1.uv = (Vec2f){uv_topleft.y, uv_bottomright.x};
    elem.rt1.uv.x = uv_bottomright.x;
    elem.rt1.uv.y = uv_topleft.y;

    elem.lb2.pos.x = center.x - size.x / 2;
    elem.lb2.pos.y = center.y - size.y / 2;
    // elem.lb2.uv = (Vec2f){uv_topleft.x, uv_bottomright.y};
    elem.lb2.uv.x = uv_topleft.x;
    elem.lb2.uv.y = uv_bottomright.y;

    elem.rt2.pos.x = center.x + size.x / 2;
    elem.rt2.pos.y = center.y + size.y / 2;
    // elem.rt2.uv = (Vec2f){uv_topleft.y, uv_bottomright.x};
    elem.rt2.uv.x = uv_bottomright.x;
    elem.rt2.uv.y = uv_topleft.y;

    elem.rb2.pos.x = center.x + size.x / 2; 
    elem.rb2.pos.y = center.y - size.y / 2;
    elem.rb2.uv = uv_bottomright;

    return elem;
}

hud_draw_elem_t create_bar(Vec2f center, Vec2f size, Vec2f uv_topleft, Vec2f uv_bottomright, float fullness)
{
    // center.x -= size.x/2;
    // size.x   *= fullness;
    // center.x += size.x/2;

    // float uv_x_length = uv_bottomright.x - uv_topleft.x;
    // uv_x_length *= fullness;
    // uv_bottomright.x = uv_topleft.x + uv_x_length;

    hud_draw_elem_t bar = create_rect(center, size, uv_topleft, uv_bottomright);

    return bar;
}

//onmc = on mouse click. True if input in this window, false otherwise;
int onmc_status_bars (game_t* game, Vec2f nmouse_pos)
{
    const Vec2f             sb_size = {0.1, 0.1};
    const hud_status_bars_t sb = game->hud_manager.storage.status_bars;

    //if inside widget
    if (nmouse_pos.x > (sb.pos.x - sb_size.x/2) and nmouse_pos.x < (sb.pos.x + sb_size.x/2) and
        nmouse_pos.y > (sb.pos.y - sb_size.y/2) and nmouse_pos.y < (sb.pos.y + sb_size.y/2))
    {
        //could check for some buttons /etc but for now its fine        
        

        return true;
    }


    return false;
}

void hd_status_bars(game_t* game)
{
    const Vec2f             sb_size = {144.f/1920*2.5, 96.f/1080*2.5};
    hud_status_bars_t sb = game->hud_manager.storage.status_bars;
    sb.pos = (Vec2f){-1.0+sb_size.x/2, +1.0 - sb_size.y/2};

    hud_draw_elem_t background; 
    // background.lt.pos
    background = create_rect(sb.pos, sb_size, (Vec2f){0, 0}, (Vec2f){144.f/512, 96.f/512});    

    vector_add(&game->hud_manager.draw_data, background);

    // float positions[6] =
    // {
    //     -0.99, 0.99,
    //     -0.99, 0.9,
    //     -0.9, 0.99,
    // };
    // float uvs[6] =
    // {
    //     0.99, 0.99,
    //     0.5, 0.99,
    //     0.99, 0.5,
    // }; 

    // glBindBuffer(GL_ARRAY_BUFFER, game->hud_manager.vbo_pos);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, &positions, GL_STATIC_DRAW);
    // glBindBuffer(GL_ARRAY_BUFFER, game->hud_manager.vbo_uvs);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, &uvs, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, );


    hud_draw_elem_t health_bar = {0};
    Vec2f hb_pos;
    hb_pos.x = sb.pos.x;
    hb_pos.y = sb.pos.y - 16.f/512;
    Vec2f hb_size = {144.f/512/2, 16.f/512/2};

    float health_fullness = 0.1;
    health_bar = create_bar(hb_pos, hb_size, (Vec2f){0, 96.f/512}, (Vec2f){144.f/512, 112.f/512}, health_fullness);

    vector_add(&game->hud_manager.draw_data, health_bar);
}

void push_status_bars_widget(game_t* game)
{
    hud_widget_t status_bars = {0};

    status_bars.on_mouse_click = onmc_status_bars;
    status_bars.handle_draw = hd_status_bars;

    push_widget(game, status_bars);
}