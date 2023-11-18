#version 330 core


in GS_OUT
{
    vec2  tileset_uv;
    float height_diff;
} fs_in;

out vec4 fragColor;

uniform sampler2D my_tileset_texture;


float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}


void main() {
    // float rand_val = random(gl_PointCoord);
    // if(fs_in.height_diff > 1.0)
    // {
    //     if (rand_val < fs_in.height_diff / 3)
    //     {
    //         discard;
    //     }
    // }
    
    fragColor = texture(my_tileset_texture, fs_in.tileset_uv);

    if (fragColor.w < 0.5)
    {
        //without this discard transparent parts of sprites do block others
        discard;
    }
    // fragColor = vec4(0.45, 0.19, 0.82, 1.0);
}