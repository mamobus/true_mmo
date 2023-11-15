#version 330 core


in vec2 hud_uv;

out vec4 fragColor;

uniform sampler2D my_hud_texture;


void main(){
    
    fragColor = texture(my_hud_texture, hud_uv);

//     if (hud_uv.x == 0.0 && hud_uv.y == 1.0)
//     {
//         fragColor = vec4(0.19, 0.82, 0.56, 1.0);
//     }
//     if (hud_uv.x == 1.0 && hud_uv.y == 0.0)
//     {
//         fragColor = vec4(0.82, 0.45, 0.19, 1.0);
//     }
//     if (hud_uv.x == 1.0 && hud_uv.y == 1.0)
//     {
//         fragColor = vec4(0.82, 0.19, 0.19, 1.0);
//     }
//     if (hud_uv.x == 0.0 && hud_uv.y == 0.0)
//     {
//         fragColor = vec4(0.27, 0.19, 0.82, 1.0);
//     }
//     if (hud_uv.x == 0.5 && hud_uv.y == 0.5)
//     {
//         fragColor = vec4(0.82, 0.19, 0.57, 1.0);
//     }
}