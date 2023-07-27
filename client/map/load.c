#include "load.h"

#define PRINT printf("line %d, function %s\n", __LINE__, __FUNCTION__);

void load_level(Game_t* game)
{
    char* map_path = "C:/Users/platonvin/Documents/tiled/gsdfgf/untitled.tmj";
    char* texture_path;
    int len;
    cute_tiled_tileset_t tileset;
    cute_tiled_map_t* map;

    game->map = cute_tiled_load_map_from_file(map_path, 0);
    map = game->map;
    tileset = game->map->tilesets[0];
    game->draw.tile_count = game->map->layers[0].data_count;


    texture_path = calloc((strlen(map_path) + strlen(tileset.image.ptr) + 1), sizeof(char));
    strcat(texture_path, map_path);
    for (len = strlen(texture_path); texture_path[len] != '/' && len > 0; len--);
    texture_path[len]='\0';
    strcat(texture_path, "/");
    strcat(texture_path, tileset.image.ptr);
    
    
    // printf("%s\n", texture_path);
    // game->draw.textureID = loadTexture(texture_path);
    // game->draw.programID = load_shaders("../client/draw/shaders/vertex.glsl", "../client/draw/shaders/fragment.glsl");
    game->draw.vertex_data = calloc(game->draw.tile_count, sizeof(Vec3));
    game->draw.tile_data   = calloc(game->draw.tile_count, sizeof(float));
    //копируем с преобразованем типа и вычислением координат
    for (size_t i = 0; i < game->draw.tile_count; i++)
    {
        game->draw.vertex_data[i].x = i % map->layers[0].width;
        game->draw.vertex_data[i].y = i / map->layers[0].width;
        game->draw.vertex_data[i].z = 0;
        game->draw.tile_data[i] = (float) game->map->layers[0].data[i];
    }
    
    for(int i = 0; i < game->draw.tile_count; i++)
    {
        if(i % map->layers[0].width == 0)
        {
            printf("\n");
        }
        printf("(%.2f,%.2f)%.2f;  ", game->draw.vertex_data[i].x, 
                                           game->draw.vertex_data[i].y, 
                                        //    game->draw.vertex_data[i].z, 
                                           game->draw.tile_data[i]);
    }
    
    // //нужно для опенгл, не трогать
    // glGenVertexArrays(1, &game->draw.VertexArrayID);
	// glBindVertexArray(game->draw.VertexArrayID);

    // glGenBuffers(1, &game->draw.vertex_buffer);
    // glBindBuffer(GL_ARRAY_BUFFER, &game->draw.vertex_buffer);
    // glBufferData(GL_ARRAY_BUFFER, game->draw.tile_count*sizeof(Vec3), game->draw.vertex_data, GL_STATIC_DRAW);

    // glGenBuffers(1, &game->draw.tile_buffer);
    // glBindBuffer(GL_ARRAY_BUFFER, &game->draw.tile_buffer);
    // glBufferData(GL_ARRAY_BUFFER, game->draw.tile_count*sizeof(float), game->draw.tile_data, GL_STATIC_DRAW);  

    // game->draw.textureID = glGetUniformLocation(game->draw.programID, "myTexture");
    
    cute_tiled_free_map(game->map);
    free(texture_path);
}

void free_level(Game_t* game)
{
    cute_tiled_free_map(game->map);
}