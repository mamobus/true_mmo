#version 460 core

// in vec3 coords;
in vec2 tileset_uv;

out vec4 fragColor;
uniform sampler2D my_tileset_texture;

void main() {
    // Use the geomCoords and geomUV to determine the final fragment color
    vec2 coord_on_a_tileset = gl_PointCoord / 32.0 + tileset_uv;
    fragColor = texture(my_tileset_texture, coord_on_a_tileset);
    if (fragColor.w < 0.5)
    {
        //withou this discard transparent parts of sprites block others
        discard;
    }
    // fragColor = vec4(0.45, 0.19, 0.82, 1.0);
}