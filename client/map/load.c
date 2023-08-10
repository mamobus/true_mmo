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

void load_map_from_file(char* map_path, map_t* map)
{
    cute_tiled_map_t* cute_map = cute_tiled_load_map_from_file(map_path, 0);
}