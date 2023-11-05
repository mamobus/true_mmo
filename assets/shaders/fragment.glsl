#version 330 core

// in vec3 coords;
in vec2  tileset_uv;
in float height_diff;

out vec4 fragColor;

uniform sampler2D my_tileset_texture;

uniform float point_size;
uniform float grid_size ;


float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}


void main() {
    // Use the geomCoords and geomUV to determine the final fragment color
    vec2 coord_on_a_tileset;
    vec2 reversed_PointCoord;
    
    // if (sign(tileset_uv.x) != -1.0)
    // {
        // vec2 scale = vec2(0.99, 0.99);
        coord_on_a_tileset = gl_PointCoord / grid_size + tileset_uv;
    // }
    // else
    // {
    //     reversed_PointCoord.x = 1.0 - gl_PointCoord.x;
    //     reversed_PointCoord.y =       gl_PointCoord.y;

    //     coord_on_a_tileset = reversed_PointCoord / (point_size / 2.0) - tileset_uv;
    // }

    float rand_val = random(gl_PointCoord);
    if(height_diff > 1.0)
    {
        if (rand_val < height_diff / 3)
        {
            discard;
        }
    }
    
    fragColor = texture(my_tileset_texture, coord_on_a_tileset);

    if (fragColor.w < 0.5)
    {
        //withou this discard transparent parts of sprites block others
        discard;
    }
    // fragColor = vec4(0.45, 0.19, 0.82, 1.0);
}