// #define _DEBUG

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "common/game_t.h"

#include <common/input.h>
#include <draw/window/window.h>
#include <draw/camera/camera.h>
#include <draw/draw.h>
#include <logic/entity.h>
#include <map/chunk.h>
#include <physics/update/update.h>
#include <network/network.h>

#define CALL(x) \
do{ \
printf("called   %s\n", #x); \
x; \
printf("returned %s\n", #x); \
}while(0)

void print_fps()
{
    static double start, stop;
    // double frame_start, frame_stop; //for lowest fps in 1 second
    static int frames;
    
    /*___________*/
    stop = glfwGetTime();
    frames++;
    if (stop-start > 1.0) //every 4 seconds
    {
        // printf("FPS=%.2lf MSPF=%lf\n", ((double)frames)/(stop-start), 1000*(stop-start)/((double)frames));
        // printf("vel %.2lf %.2lf %.2lf\n", game.player.vel.x, game.player.vel.y, game.player.vel.z);
        // printf("pos %.2lf %.2lf %.2lf\n", game.player.pos.x, game.player.pos.y, game.player.pos.z);
        // printf("acl %.2lf %.2lf %.2lf\n", game.player.acl.x, game.player.acl.y, game.player.acl.z);
        start = stop;
        frames = 0;
    }
    /*___________*/
}

void update_time(game_t* game)
{
    double current_time = glfwGetTime();
    game->time_elapsed    = current_time - game->last_frame_time;
    game->last_frame_time = current_time;
}

//is accessed by "extern" in input
game_t game = {0};

int main()
{
    game.player.pos.z = 1;

    create_window(&game);
    // Sleep(1000);
    glfwSwapInterval(1);

    setup_draw(&game);

    setup_input(&game);

    load_chunk_manager("../assets/map/chunk_manager", "../assets/map/chunk_file", &game);
    load_all_chunks(&game);

    entity_create_manager(&game);
    hud_create_manager(&game);

// #if defined(_WITH_SERVER)
    // net_create_manager(&game);
    


    // entity_t mob_that_is_player_for_now = {0};
    // mob_that_is_player_for_now.id = 1;
    // mob_that_is_player_for_now.type = 1;
    // mob_that_is_player_for_now. 
    // mob_that_is_player_for_now.state = MOB_MOVE_BIT | MOB_LEFT_BIT | MOB_DOWN_BIT;
    // CALL(entity_add(mob_that_is_player_for_now, 1001, &game));

    entity_t player = {0};
    player.id = 1;
    player.state = PLAYER_MOVE_BIT | PLAYER_LEFT_BIT | PLAYER_DOWN_BIT;
    game.player.state = PLAYER_MOVE_BIT;
    // player.state = MOB_MOVE_BIT | MOB_LEFT_BIT;
    // player.

    CALL(entity_add(player, 101, &game));

    // GLFW_KEY_LAST

    while(!glfwWindowShouldClose(game.window.pointer) && glfwGetKey(game.window.pointer, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glfwPollEvents();
        print_fps();

        // info

        update_time(&game);
        update_player(&game);
        update_camera(&game);
        // net_update(&game);
                
        //update mob but for now its player
        entity_t* player_ent = entity_find(1, 101, &game);
        game.player.state = PLAYER_MOVE_BIT | player_get_direction_bits(game.player.dir);
        printf("state %X\n", game.player.state);
        // printf("%d ", player_ent->sprite_num);
        player_ent->pos   = game.player.pos;
        player_ent->state = game.player.state;
        // if()

        entities_prepare_for_drawing(&game);
        draw(&game);
        glfwSwapBuffers(game.window.pointer);
        
    }

    printf("PROG_END\n");

    hud_destroy_manager(&game);
    entity_destroy_manager(&game);
    chunk_destroy_manager(&game);
    // net_destroy_manager(&game);

    printf("MANAGERS_DESTROYED\n");

    glfwTerminate();
    terminate_draw(&game);
    // dasd

    return 228;
}