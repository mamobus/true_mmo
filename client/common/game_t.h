#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//structs

#include <draw/camera/camera_t.h>
#include <draw/window/window_t.h>
#include <draw/textures/texture_manager_t.h>
#include <logic/entity_t.h>
#include <map/chunk_t.h>
#include <physics/collision/collision_t.h>
#include <HUD/hud_t.h>
#include <network/network_t.h>

#include <common/player.h>

typedef struct 
{
    GLuint raytracer_progID; 
    GLuint denoiser_progID; 
    GLuint framebuffer;
    GLuint framebuffer_1;
    GLuint normalbuffer;
    GLuint framebuffer_2;
    GLuint uni_time;
    GLuint uni_camerapos_raytrace;
    GLuint uni_camerashift_denoise;
    GLuint vbo; //6 verts to render final texture
    GLuint tSet_ReflectNopacity, tSet_EmmitNsmooth;

    GLuint FBO, drawn_ents;
    
    // int voxel_height;
    // int voxels;// 16*16
    // int width, height;
    int* data;
    GLuint ssbo, uni_ssbo;
} raytracer;

typedef struct uniforms_t
{
    GLuint map_tileset;
    GLuint hud_set;
    GLuint camera_pos;
    // GLuint window_size;
    // GLuint textureID;
    GLuint in_textr_size;
    GLuint in_world_size;
} uniforms_t;

typedef struct game_t
{
    GLuint tile_progID; 
    GLuint hud_progID; 

    raytracer RT;

    GLuint tileset_textureID;
    GLuint VertexArrayID;
    uniforms_t uni;

    camera_t camera;
    window_t window;

    chunk_manager_t chunk_manager;

    // texture_manager_t texture_manager;

    float scale; //scales ONLY map & entities
    entity_manager_t entity_manager;
    hud_manager_t hud_manager;

    //он упрлс
    network_manager_t net_mngr;
    
    player_t player;

    double last_frame_time;
    double time_elapsed;
    // double simulation_time_left;
} game_t;
