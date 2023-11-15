#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//structs

#include <draw/camera/camera_t.h>
#include <draw/window/window_t.h>
#include <draw/textures/texture_manager_t.h>
#include <logic/mob/mob_t.h>
#include <logic/projectile/projectile_t.h>
#include <logic/effect/effect_t.h>
#include <map/chunk_t.h>
#include <physics/collision/collision_t.h>
#include <HUD/hud_t.h>

#include <common/player.h>


typedef struct uniforms_t
{
    GLuint map_tileset;
    GLuint hud_set;
    GLuint camera_pos;
    GLuint window_size;
    // GLuint textureID;
    GLuint point_size;
    GLuint grid_size;
} uniforms_t;

typedef struct game_t
{
    GLuint map_progID; 
    GLuint hud_progID; 
    GLuint tileset_textureID;
    GLuint VertexArrayID;
    uniforms_t uni;

    camera_t camera;
    window_t window;

    chunk_manager_t chunk_manager;

    texture_manager_t texture_manager;

    mob_manager_t mob_manager;
    projectile_manager_t projectile_manager;
    effect_manager_t effect_manager;
    hud_manager_t hud_manager;
    
    player_t player;

    double last_frame_time;
    double time_elapsed;
    // double simulation_time_left;
} game_t;
