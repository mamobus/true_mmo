#version 460 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec3 coords[];
in float uv[];

out vec3 geomCoords;
out float geomUV;

void main() {
    geomCoords = coords[0];
    geomUV = uv[0];
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    geomCoords = coords[0] + vec3(1.0, 0.0, 0.0); // Right neighbor
    geomUV = uv[0];
    gl_Position = gl_in[0].gl_Position + vec4(1.0, 0.0, 0.0, 0.0);
    EmitVertex();

    geomCoords = coords[0] + vec3(0.0, 1.0, 0.0); // Top neighbor
    geomUV = uv[0];
    gl_Position = gl_in[0].gl_Position + vec4(0.0, 1.0, 0.0, 0.0);
    EmitVertex();

    geomCoords = coords[0] + vec3(1.0, 1.0, 0.0); // Diagonal neighbor
    geomUV = uv[0];
    gl_Position = gl_in[0].gl_Position + vec4(1.0, 1.0, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}