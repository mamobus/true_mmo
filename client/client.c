// #define _DEBUG_
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "common/game_t.h"

#include <common/input.h>
#include <draw/window/window.h>
#include <draw/camera/camera.h>
#include <draw/draw.h>
#include <logic/mob/mob.h>
#include <map/chunk.h>
#include <physics/update/update.h>

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
        printf("FPS=%.2lf MSPF=%lf\n", ((double)frames)/(stop-start), 1000*(stop-start)/((double)frames));
        printf("vel %.2lf %.2lf %.2lf\n", game.player.vel.x, game.player.vel.y, game.player.vel.z);
        printf("pos %.2lf %.2lf %.2lf\n", game.player.pos.x, game.player.pos.y, game.player.pos.z);
        printf("acl %.2lf %.2lf %.2lf\n", game.player.acl.x, game.player.acl.y, game.player.acl.z);
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
    game.player.pos.z = 10;

    create_window(&game);
    glfwSwapInterval(1);

    setup_draw(&game);

    setup_input(&game);

    load_chunk_manager("../assets/map/chunk_manager", "../assets/map/chunk_file", &game);
    load_all_chunks(&game);

    mob_create_manager(&game);


    mob_t mob_that_is_player_for_now = {0};
    mob_that_is_player_for_now.id = 1;
    mob_that_is_player_for_now.state = MOB_MOVE_BIT || MOB_LEFT_BIT || MOB_DOWN_BIT;
    mob_add(mob_that_is_player_for_now, 0, &game);

    while(!glfwWindowShouldClose(game.window.pointer) && glfwGetKey(game.window.pointer, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glfwPollEvents();
        print_fps();

        update_time(&game);
        update_player(&game);
        update_camera(&game);
        
        //update mob but for now its player
        mob_t* player_mob = mob_find_by_id_and_type(1, 0, &game);
        player_mob->pos = game.player.pos;

        draw(&game);
        glfwSwapBuffers(game.window.pointer);

    }

    printf("PROG_END");

    glfwTerminate();
    terminate_draw(&game);
    // dasd
}