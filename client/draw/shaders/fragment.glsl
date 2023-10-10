#version 460 core

// in vec3 coords;
in float tileset_uv;

out vec4 fragColor;

void main() {
    // Use the geomCoords and geomUV to determine the final fragment color
    coord_on_a_tileset = gl_PointCoord / 32.0 + tileset_uv;
    fragColor = texture2D(my_tileset_texture, coord_on_a_tileset);
}