// #define _DEBUG_
#define GLEW_STATIC
#include <GL/glew.h>
// #include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "common/game.h"
#include "common/window.h"
#include "draw/draw.h"
// #include "load/chunk.h"
double start, stop;
int frames;
int main()
{
    assert(glfwInit());

    Game_t game;

    give_this_game_a_window(&game);
    glfwSwapInterval(0);

    init_draw(&game.draw);

    while(!glfwWindowShouldClose(game.window.pointer))
    {
stop = glfwGetTime();
frames++;
if (stop-start > 1)
{
    printf("fps = %3lf\n", ((double)frames)/(stop-start));
    start = stop;
    frames = 0;
}

        glfwPollEvents();
        draw(&game.draw);
        glfwSwapBuffers(game.window.pointer);
    }


    glfwTerminate();
    terminate_draw(&game.draw);
    // dasd
}