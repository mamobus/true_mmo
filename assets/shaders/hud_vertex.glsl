#version 330 core

layout(location = 0) in vec2 vertex_coords;
layout(location = 1) in vec2 uv;

out vec2 hud_uv;


void main(){    
    vec3 clip_coords;

    clip_coords.xy = vertex_coords;
    // clip_coords.z = -1.0;
    clip_coords.z = 1.0;

    gl_Position  = vec4(clip_coords, 1.0);
    hud_uv = uv;
    // hud_uv.x = 0.4;    
    // hud_uv.y = 0.7;    
}