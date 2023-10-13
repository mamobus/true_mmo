#version 460 core

layout(location = 0) in vec3 vertex_coords;
layout(location = 1) in float tile_num;

out vec2 tileset_uv;

uniform vec2 camera_pos; 
uniform vec2 window_size; 

mat3 transform = mat3(
    +1.0, -0.5,  -1.0,
    -1.0, -0.5,  -1.0,
    +0.0, +0.0,  0
);

// vec2 sf = vec2(64.0, 64.0);

void main(){
    vec3 clip_coords = transform * vertex_coords;
    clip_coords.xy = clip_coords.xy * 64.0 / window_size.yx;
    clip_coords.xy -= camera_pos.xy;
    clip_coords.z /= 1000;
    // clip_coords.x -= stride_xy.x;
    // clip_coords.y -= stride_xy.y;
    // gl_Position = vec4(0.1,-0.1, 0.5, 1.0);
    gl_Position = vec4(clip_coords, 1.0);
    gl_PointSize = 64.0;

    //top left corner 
    tileset_uv.x = fract(tile_num / 32.0);
    tileset_uv.y = floor(tile_num / 32.0) / 32.0;
}