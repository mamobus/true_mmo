#version 460 core

layout(location = 0) in vec3 vertex_coords;
layout(location = 1) in float tile_num;

out vec2 coords;
out vec2 uv;

void main(){
    coords = vertex_coords;
    UV = vec2(tile_num, 0)
    gl_Position = vec4(vertexCoords, 1.0);
}