#version 330 core

layout(location = 0) in vec3  vertex_coords;
layout(location = 1) in float tile_num;

out VS_OUT
{
    vec2  tileset_uv;
    float height_diff;
} vs_out;

uniform vec3 camera_pos; 

uniform vec2 in_world_size;
uniform vec2 in_textr_size;

// mat3 transform = mat3(
//     +1.0, -0.5,  -1.0,
//     -1.0, -0.5,  -1.0,
//     +0.0, +1.0,  +0.0
// );


void main(){

    //apply camera and use matrix
	vec3 ray_dir    = normalize(vec3(-0.612375, -0.612375, 0));
	// vec3 ray_dir = normalize(vec3(-2.8284271, -2.8284271, -3));

	vec3 horizline = normalize(vec3(1,-1,0));
	vec3 vertiline = normalize(cross(ray_dir, horizline));
	//they define plane of rendeting
	
	float view_width  = 1920 / 32.0; //in block_diags
	float view_height = 1080 / 32.0; //in blocks

    vec3 vertexRelativeToCameraPos = vertex_coords - camera_pos;
    // vec3 vertexRelativeToCameraPos = vertex_coords - ray_dir * dot(ray_dir, vertex_coords);
    vec3 clip_coords;
    clip_coords.x = dot(vertexRelativeToCameraPos, horizline) / view_width  / 3;
    clip_coords.y = dot(vertexRelativeToCameraPos, vertiline) / view_height / 3;
    clip_coords.z = dot(vertexRelativeToCameraPos, ray_dir) / 3;
    //for propper sorting

    // vec3 clip_coords    = transform * (vertex_coords - camera_pos);
    //      clip_coords.xy = clip_coords.xy * in_world_size.xy / 2;


    vs_out.height_diff = vertex_coords.z - camera_pos.z;


    gl_Position  = vec4(clip_coords, 1.0);

    //top left corner 
    vs_out.tileset_uv.x = fract(abs(tile_num) * in_textr_size.x) * sign(tile_num);
    if(tile_num < 0)
    {
        vs_out.tileset_uv.x -= in_textr_size.x; //cause we stick to left-top corners
    }
    vs_out.tileset_uv.y = floor(abs(tile_num) * in_textr_size.x) * in_textr_size.y;

    // vs_out.tileset_uv.x = 1.f/    
    // vs_out.tileset_uv    
}