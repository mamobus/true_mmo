#version 330 core

// in vec3 coords;
in vec2 tileset_uv;

out vec4 fragColor;

uniform sampler2D my_tileset_texture;

uniform float point_size;
uniform float grid_size ;

void main() {
    // Use the geomCoords and geomUV to determine the final fragment color
    vec2 coord_on_a_tileset;
    vec2 reversed_PointCoord;
    
    if (sign(tileset_uv.x) != -1.0)
    {
        coord_on_a_tileset = gl_PointCoord / grid_size + tileset_uv;
    }
    else
    {
        reversed_PointCoord.x = 1.0 - gl_PointCoord.x;
        reversed_PointCoord.y =       gl_PointCoord.y;

        coord_on_a_tileset = reversed_PointCoord / (point_size / 2.0) - tileset_uv;
    }

    
    fragColor = texture(my_tileset_texture, coord_on_a_tileset);
    

    if (fragColor.w < 0.5)
    {
        //withou this discard transparent parts of sprites block others
        discard;
    }
    // fragColor = vec4(0.45, 0.19, 0.82, 1.0);
}