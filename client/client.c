// #define _DEBUG_
#define GLEW_STATIC
#include <GL/glew.h>
// #include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "common/input.h"
#include "common/game.h"
// #include "common/window.h"
// #include "draw/draw.h"
// #include "load/chunk.h"


double start, stop;
int frames;
int main()
{
    assert(glfwInit());

    Game_t game = {0};

    give_this_game_a_window(&game);
    // glfwSwapInterval(0);

    init_draw(&game.draw);

    setup_input(&game);

    while(!glfwWindowShouldClose(game.draw.window.pointer) && glfwGetKey(game.draw.window.pointer, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
/*___________*/
stop = glfwGetTime();
frames++;
if (stop-start > 1)
{
    printf("fps = %3lf\n", ((double)frames)/(stop-start));
    start = stop;
    frames = 0;
}
/*___________*/

        glfwPollEvents();
        draw(&game.draw);
        glfwSwapBuffers(game.draw.window.pointer);
    }

    printf("PROG_END");

    glfwTerminate();
    terminate_draw(&game.draw);
    // dasd
}