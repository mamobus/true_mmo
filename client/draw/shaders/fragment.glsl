#version 460 core

in vec3 geomCoords;
in float geomUV;

out vec4 fragColor;

void main() {
    // Use the geomCoords and geomUV to determine the final fragment color
    fragColor = vec4(1.0, 0.0, 0.0, 1.0); // Red color as an example
}