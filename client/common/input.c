#include "input.h"

void move_camera_x(float x)
{
    camera_o->position.x += x;
}
void move_camera_y(float y)
{
    camera_o->position.y += y;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        move_camera_x(0.1f);
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        move_camera_x(-0.1f);
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        move_camera_y(0.1f);
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        move_camera_y(-0.1f);
    }
}   

void setup_input(Game_t* game)
{
    camera_o = &game->draw.camera;

    glfwSetKeyCallback(game->draw.window.pointer, key_callback);
}