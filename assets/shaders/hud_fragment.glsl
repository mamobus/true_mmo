#version 330 core


in vec2 hud_uv;

out vec4 fragColor;

uniform sampler2D hud_texture;


void main(){
    fragColor = texture(hud_texture, hud_uv);
}