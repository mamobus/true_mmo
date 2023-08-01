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




//load chunks one by one into vbos and calloced memory. Use SQL to manage chunks in file
void create_shunk_system()
{
    chunk_system_t chunk_system;
    chunk_system.chunks = calloc(chunk_system.max, sizeof(chunk_t));

    //load surrounding chunks
}

void load_map_to_chunks()
{
    //calculate chunk xy\s and load_chunk them into chunk_system

}

chunk_t load_chunk_from_sql(int x, int y)
{
    //get chunk data and chunk tile_count
}

void load_chunk(chunk_system_t* chunk_system, int chunk_num)
{
    int x, y;
    //load chunk from sql
    chunk_t new_chunk = load_chunk_from_sql(x, y);

    chunk_system->chunks[chunk_num] = new_chunk;
}

void free_chunk(chunk_system_t* chunk_system, int chunk_num)
{
    //TODO clear on release but im not shure
    assert(chunk_system->chunks[chunk_num].data != 0);
    
    free(chunk_system->chunks[chunk_num].data);
    chunk_system->chunks[chunk_num].tile_count = 0;
}

void handle_shunk_system()
{
    //if moved enough then unload chunks behind and load chunks in front using load_&free_chunk
}
