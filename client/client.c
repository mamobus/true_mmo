// #define _DEBUG_
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "common/game.h"
#include "common/window.h"
#include "draw/draw.h"
// #include "load/chunk.h"

int main()
{
    assert(glfwInit());

    Game_t game;

    init_draw(&game.draw);

    give_this_game_a_window(&game);

    while(!glfwWindowShouldClose(game.window.pointer))
    {
        glfwPollEvents();
        draw(&game.draw);
        glfwSwapBuffers(game.window.pointer);
    }

    glfwTerminate();
    terminate_draw(&game.draw);
    // dasd
}