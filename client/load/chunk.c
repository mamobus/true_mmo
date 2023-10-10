#include "chunk.h"

#define PRINT printf("line %d, function %s\n", __LINE__, __FUNCTION__);

void load_chunk_manager(char* manager_file_name, char* chunk_file_name, chunk_manager_t* chunk_manager) 
{
    FILE* manager_file = fopen(manager_file_name, "wb");
    FILE* chunk_file   = fopen(chunk_file_name,   "wb");

    chunk_manager->chunk_file = chunk_file;

    // Read the height and width of the 2D array of chunk_t objects from the file
    fread(&chunk_manager->height, sizeof(int), 1, manager_file);
    fread(&chunk_manager->width, sizeof(int), 1, manager_file);

    // Allocate memory for the height*width chunks
    chunk_manager->chunks = calloc(chunk_manager->height * chunk_manager->width, sizeof(chunk_t*));
    // assert(chunk_manager->chunks != 0);

    // Read the 2D array of chunk_t objects from the file
    for (int y = 0; y < chunk_manager->height; y++) 
    {
        for (int x = 0; x < chunk_manager->width; x++) 
        {
            chunk_t* chunk = &(chunk_manager->chunks[x + y*chunk_manager->height]);
            chunk->vbo = 0; // not loaded
            chunk->tiles = NULL; // not loaded

            // Read the chunk's offset and length
            fread(&chunk->offset, sizeof(int), 1, manager_file);
            fread(&chunk->tile_count, sizeof(int), 1, manager_file);
        }
    }
}

void free_chunk_manager(chunk_manager_t* chunk_manager) 
{
    free_all_chunks(chunk_manager);
    free(chunk_manager->chunks);
    return;
}

void load_chunk(chunk_manager_t* chunk_manager, int x, int y)
{
    //if is loaded
    chunk_t* chunk = &chunk_manager->chunks[x + y*chunk_manager->width];
    if (chunk->tiles != 0)
    {
        return; //cause already loaded
    }
    //so its not loaded
    //now we have buffer
    chunk->tiles = calloc(chunk->tile_count, sizeof(tile_t));
    //lets read into it
    fread(chunk->tiles, sizeof(tile_t), chunk->tile_count, chunk_manager->chunk_file);

    glGenBuffers(1, &chunk->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, chunk->vbo);
    glBufferData(GL_ARRAY_BUFFER, chunk->tile_count * sizeof(tile_t), chunk->tiles, GL_STATIC_DRAW);
}

void free_chunk(chunk_manager_t* chunk_manager, int x, int y)
{
    //if is not loaded
    chunk_t* chunk = &chunk_manager->chunks[x + y*chunk_manager->width];
    if (chunk->tiles == 0)
    {
        return; //cause already unloaded
    }

    free(chunk->tiles);

    glDeleteBuffers(1, &chunk->vbo);
}

void load_all_chunks(chunk_manager_t* chunk_manager)
{
    for(int column=0; column < chunk_manager->width; column++)
    {
        for(int line=0; line < chunk_manager->height; line++)
        {
            load_chunk(chunk_manager, column, line);
        }
    }
}

void free_all_chunks(chunk_manager_t* chunk_manager)
{
    for(int column=0; column < chunk_manager->width; column++)
    {
        for(int line=0; line < chunk_manager->height; line++)
        {
            free_chunk(chunk_manager, column, line);
        }
    }
}