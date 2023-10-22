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

void print_fps()
{
    static double start, stop;
    // double frame_start, frame_stop; //for lowest fps in 1 second
    static int frames;
    
    /*___________*/
    stop = glfwGetTime();
    frames++;
    if (stop-start > 4.0) //every 4 seconds
    {
        printf("FPS=%.2lf MSPF=%lf\n", ((double)frames)/(stop-start), 1000*(stop-start)/((double)frames));
        start = stop;
        frames = 0;
    }
    /*___________*/
}


int main()
{
    game_t game = {0};

    create_window(&game);
    // glfwSwapInterval(0);

    setup_draw(&game);

    setup_input(&game);

    while(!glfwWindowShouldClose(game.window.pointer) && glfwGetKey(game.window.pointer, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        print_fps();

        glfwPollEvents();
        draw(&game);
        glfwSwapBuffers(game.window.pointer);
    }

    printf("PROG_END");

    glfwTerminate();
    terminate_draw(&game);
    // dasd
}