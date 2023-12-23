#include "input.h"
#include <math.h>

void set_dirX(float x)
{
    game.player.dir.x = x;
}
void set_dirY(float y)
{
    game.player.dir.y = y;
}
void set_dirZ(float z)
{
    game.player.dir.z = z;
}
void set_dir(vec3d dir)
{
    game.player.dir = dir;
}
void add_dir(vec3d dir)
{
    game.player.dir.x += dir.x;
    game.player.dir.y += dir.y;
    game.player.dir.z += dir.z;

    // game.player.pos.x += dir.x * 0.0;
    // game.player.pos.y += dir.y * 0.0;
    // game.player.pos.z += dir.z * 0.0;
}
void sub_dir(vec3d dir)
{
    game.player.dir.x -= dir.x;
    game.player.dir.y -= dir.y;
    game.player.dir.z -= dir.z;
}

// vec3d right = {}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // printf("key pressed BTW\n");
    if (key == GLFW_KEY_D && action == GLFW_PRESS){    
        // set_dirX(+1.0f);
        // set_dirY(-1.0f);
        add_dir((vec3d){+1,-1,0});
    }
    if (key == GLFW_KEY_D && action == GLFW_RELEASE){
        // set_dirX(0);
        // set_dirY(0);
        sub_dir((vec3d){+1,-1,0});
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS){
        // set_dirX(-1.0f);
        // set_dirY(+1.0f);
        add_dir((vec3d){-1,+1,0});
    }
    if (key == GLFW_KEY_A && action == GLFW_RELEASE){   
        // set_dirX(0);
        // set_dirY(0);
        sub_dir((vec3d){-1,+1,0});
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS){
        // set_dirX(-1.0f);
        // set_dirY(-1.0f);
        add_dir((vec3d){-1,-1,0});
    }
    if (key == GLFW_KEY_W && action == GLFW_RELEASE){
        // set_dirX(0);
        // set_dirY(0);
        sub_dir((vec3d){-1,-1,0});
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS){
        // set_dirX(+1.0f);
        // set_dirY(+1.0f);
        add_dir((vec3d){+1,+1,0});
    }
    if (key == GLFW_KEY_S && action == GLFW_RELEASE){
        // set_dirX(0);
        // set_dirY(0);
        sub_dir((vec3d){+1,+1,0});
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        // game.player.pos.z += 5.0;
        game.player.vel.z = +3.33;
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE){
        set_dirZ(0);
    }

    // if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS){
    //     set_dirZ(-1.0f);    
    // }
    // if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE){
    //     set_dirZ(0);
    // }
}   

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    double x, y;
    x = xpos - 1920/2;
    y = ypos - 1080/2;

    double distance_from_center = x*x + y*y;

    if (distance_from_center > 5.0)
    {
        game.player.dir.x = x / sqrt(distance_from_center); 
        game.player.dir.y = y / sqrt(distance_from_center); 
    }
    else game.player.dir = (vec3d){0,0,0};
}

void setup_input(game_t* game)
{
    glfwSetKeyCallback(game->window.pointer, key_callback);
    // glfwSetCursorPosCallback(game->window.pointer, cursor_position_callback);
}