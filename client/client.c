#define GLEW_STATIC
#define _DEBUG_
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "common/game.h"
#include "common/window.h"
#include "draw/draw.h"
#include "map/load.h"

int main()
{
    assert(glfwInit());

    Game_t game;

    // give_this_game_a_window(&game);

    // load_level(&game);

    while(!glfwWindowShouldClose(game.window.pointer))
    {
        glfwPollEvents();
    }

    glfwTerminate();
    // dasd
}