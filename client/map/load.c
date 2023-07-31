#include "load.h"

#define PRINT printf("line %d, function %s\n", __LINE__, __FUNCTION__);

char* get_tileset_path(char* map_path, char* relative_tileset_path)
{
    int len;
    char* tileset_path;
    tileset_path = calloc((strlen(map_path) + strlen(relative_tileset_path) + 1), sizeof(char));
    strcat(tileset_path, map_path);
    for (len = strlen(tileset_path); tileset_path[len] != '/' && len > 0; len--);
    tileset_path[len]='\0';
    strcat(tileset_path, "/");
    strcat(tileset_path, relative_tileset_path);
}

void load_level(Game_t* game)
{
    char* map_path = "C:/prog/true_mmo/assets/map/map.tmj";
    char* tileset_path = "C:/prog/true_mmo/assets/tileset/sprite.png";
    cute_tiled_tileset_t tileset;
    cute_tiled_map_t* map;

    //загружаемся
    game->map = cute_tiled_load_map_from_file(map_path, 0);
    map = game->map;
    tileset = game->map->tilesets[0];
    
    // //нужно для опенгл, не трогать
    // glGenVertexArrays(1, &game->draw.VertexArrayID);
	// glBindVertexArray(game->draw.VertexArrayID);

    // glGenBuffers(1, &game->draw.vertex_buffer);
    // glBindBuffer(GL_ARRAY_BUFFER, &game->draw.vertex_buffer);
    // glBufferData(GL_ARRAY_BUFFER, game->draw.tile_count*sizeof(Vec3), game->draw.vertex_data, GL_STATIC_DRAW);

    // glGenBuffers(1, &game->draw.tile_buffer);
    // glBindBuffer(GL_ARRAY_BUFFER, &game->draw.tile_buffer);
    // glBufferData(GL_ARRAY_BUFFER, game->draw.tile_count*sizeof(float), game->draw.tile_data, GL_STATIC_DRAW);  

    // game->draw.uni.textureID = glGetUniformLocation(game->draw.programID, "myTexture");
    
    cute_tiled_free_map(game->map);
}

void free_level(Game_t* game)
{
    cute_tiled_free_map(game->map);
}

/*
chunk:
int its_x, its_y, tile_count
{x, y, z, tile_image} [tile_count] tiles

*/