#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT
{
    vec2  tileset_uv;
    float height_diff;
} gs_in[];

out GS_OUT
{
    vec2  tileset_uv;
    float height_diff;
} gs_out;

uniform vec2 in_world_size;
uniform vec2 in_textr_size; 

void main() 
{    
    // //left-top
    // gl_Position = gl_in[0].gl_Position + vec4(-in_world_size.x/2, +in_world_size.y/2, 0.0, 0.0); 
    // gs_out.height_diff = gs_in[0].height_diff;
    // gs_out.tileset_uv  = gs_in[0].tileset_uv + vec2(-in_textr_size.x/2, +in_textr_size.y/2);
    // EmitVertex();

    // //left-bottom
    // gl_Position = gl_in[0].gl_Position + vec4(-in_world_size.x/2, -in_world_size.y/2, 0.0, 0.0); 
    // gs_out.height_diff = gs_in[0].height_diff;
    // gs_out.tileset_uv  = gs_in[0].tileset_uv + vec2(-in_textr_size.x/2, -in_textr_size.y/2);
    // EmitVertex();
    
    // //right-top
    // gl_Position = gl_in[0].gl_Position + vec4(+in_world_size.x/2, +in_world_size.y/2, 0.0, 0.0); 
    // gs_out.height_diff = gs_in[0].height_diff;
    // gs_out.tileset_uv  = gs_in[0].tileset_uv + vec2(+in_textr_size.x/2, +in_textr_size.y/2);
    // EmitVertex();

    // //right-bottom
    // gl_Position = gl_in[0].gl_Position + vec4(+in_world_size.x/2, -in_world_size.y/2, 0.0, 0.0); 
    // gs_out.height_diff = gs_in[0].height_diff;
    // gs_out.tileset_uv  = gs_in[0].tileset_uv + vec2(+in_textr_size.x/2, -in_textr_size.y/2);
    // EmitVertex();


    //origin point in tileset is top-left 
    //left-top
    gl_Position = gl_in[0].gl_Position + vec4(-in_world_size.x/2, +in_world_size.y/2, 0.0, 0.0); 
    gs_out.height_diff = gs_in[0].height_diff;
    gs_out.tileset_uv  = gs_in[0].tileset_uv + vec2(0.0, 0.0);
    // gs_out.tileset_uv  = vec2(0, 0);
    EmitVertex();

    //left-bottom
    gl_Position = gl_in[0].gl_Position + vec4(-in_world_size.x/2, -in_world_size.y/2, 0.0, 0.0); 
    gs_out.height_diff = gs_in[0].height_diff;
    gs_out.tileset_uv  = gs_in[0].tileset_uv + vec2(0.0, +in_textr_size.y);
    // gs_out.tileset_uv  = vec2(0, shift);
    EmitVertex();
    
    //right-top
    gl_Position = gl_in[0].gl_Position + vec4(+in_world_size.x/2, +in_world_size.y/2, 0.0, 0.0); 
    gs_out.height_diff = gs_in[0].height_diff;
    gs_out.tileset_uv  = gs_in[0].tileset_uv + vec2(+in_textr_size.x, 0.0);
    // gs_out.tileset_uv  = vec2(shift, 0);
    EmitVertex();

    //right-bottom
    gl_Position = gl_in[0].gl_Position + vec4(+in_world_size.x/2, -in_world_size.y/2, 0.0, 0.0); 
    gs_out.height_diff = gs_in[0].height_diff;
    gs_out.tileset_uv  = gs_in[0].tileset_uv + vec2(+in_textr_size.x, +in_textr_size.y);
    // gs_out.tileset_uv  = vec2(shift, shift);
    EmitVertex();
    
    EndPrimitive();
}  