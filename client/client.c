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
// double frame_start, frame_stop; //for lowest fps in 1 second
int frames;
int main()
{
    assert(glfwInit());

    Game_t game = {0};

    give_this_game_a_window(&game);
    glfwSwapInterval(0);

    init_draw(&game.draw);

    setup_input(&game);

    while(!glfwWindowShouldClose(game.draw.window.pointer) && glfwGetKey(game.draw.window.pointer, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
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

        glfwPollEvents();
        draw(&game.draw);
        glfwSwapBuffers(game.draw.window.pointer);
    }

    printf("PROG_END");

    glfwTerminate();
    terminate_draw(&game.draw);
    // dasd
}