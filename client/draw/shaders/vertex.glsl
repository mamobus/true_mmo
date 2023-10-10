#version 460 core

layout(location = 0) in vec3 vertex_coords;
layout(location = 1) in float tile_num;

// out vec3 screen_coords;
out vec2 tileset_uv;

void main(){
    clip_coords = vertex_coords / 16.0;
    clip_coords.z = 1.0;  
    gl_Position = vec4(clip_coords, 1.0);
    gl_PointSize = 16.0;

    //top left corner 
    tileset_uv.x = fract(tile_num / 32.0);
    tileset_uv.y = floor(tile_num / 32.0) / 32.0;
    // tileset_uv.x = tile_num / 32.0;
    // tileset_uv.x = floor(tile_num / 32.0);
}