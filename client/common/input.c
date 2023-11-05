#include "input.h"

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
void set_dir(Vec3 dir)
{
    game.player.dir = dir;
}
void add_dir(Vec3 dir)
{
    game.player.dir.x += dir.x;
    game.player.dir.y += dir.y;
    game.player.dir.z += dir.z;
}
void sub_dir(Vec3 dir)
{
    game.player.dir.x -= dir.x;
    game.player.dir.y -= dir.y;
    game.player.dir.z -= dir.z;
}

// Vec3 right = {}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // printf("key pressed BTW\n");
    if (key == GLFW_KEY_D && action == GLFW_PRESS){    
        // set_dirX(+1.0f);
        // set_dirY(-1.0f);
        add_dir((Vec3){+1,-1,0});
    }
    if (key == GLFW_KEY_D && action == GLFW_RELEASE){
        // set_dirX(0);
        // set_dirY(0);
        sub_dir((Vec3){+1,-1,0});
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS){
        // set_dirX(-1.0f);
        // set_dirY(+1.0f);
        add_dir((Vec3){-1,+1,0});
    }
    if (key == GLFW_KEY_A && action == GLFW_RELEASE){   
        // set_dirX(0);
        // set_dirY(0);
        sub_dir((Vec3){-1,+1,0});
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS){
        // set_dirX(-1.0f);
        // set_dirY(-1.0f);
        add_dir((Vec3){-1,-1,0});
    }
    if (key == GLFW_KEY_W && action == GLFW_RELEASE){
        // set_dirX(0);
        // set_dirY(0);
        sub_dir((Vec3){-1,-1,0});
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS){
        // set_dirX(+1.0f);
        // set_dirY(+1.0f);
        add_dir((Vec3){+1,+1,0});
    }
    if (key == GLFW_KEY_S && action == GLFW_RELEASE){
        // set_dirX(0);
        // set_dirY(0);
        sub_dir((Vec3){+1,+1,0});
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        set_dirZ(1.0f);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE){
        set_dirZ(0);
    }

    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS){
        set_dirZ(-1.0f);    
    }
    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE){
        set_dirZ(0);
    }
}   

void setup_input(game_t* game)
{
    glfwSetKeyCallback(game->window.pointer, key_callback);
}