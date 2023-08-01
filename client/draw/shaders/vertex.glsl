#version 460 core

layout(location = 0) in vec3 vertex_coords;
layout(location = 1) in float tile_num;

out vec2 screen_coords;
out vec2 tileset_uv;

mat3 transformation = 
{
    
}

void main(){
    screen_coords = vertex_coords;
    tileset_uv = vec2(tile_num, 0)
    gl_Position = vec4(vertexCoords, 1.0);
}