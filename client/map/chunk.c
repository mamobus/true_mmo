#include "chunk.h"

// #define PRINT printf("line %d, function %s\n", __LINE__, __FUNCTION__);

void load_chunk_manager(char* manager_file_name, char* chunk_file_name, game_t* game) 
{
    FILE* manager_file = fopen(manager_file_name, "rb");
    FILE* chunk_file   = fopen(chunk_file_name,   "rb");
    assert(manager_file != 0);
    assert(chunk_file != 0);

    game->chunk_manager.chunk_file = chunk_file;

    // Read the height and width of the 2D array of chunk_t objects from the file
    assert(fread(&game->chunk_manager.height, sizeof(int), 1, manager_file)==1);
    assert(fread(&game->chunk_manager.width , sizeof(int), 1, manager_file)==1);

    // Allocate memory for the height*width chunks
    game->chunk_manager.chunks = calloc(game->chunk_manager.height * game->chunk_manager.width, sizeof(chunk_t));
    // assert(chunk_manager->chunks != 0);

    // Read the 2D array of chunk_t objects from the file
    for (int y = 0; y < game->chunk_manager.height; y++) 
    {
        for (int x = 0; x < game->chunk_manager.width; x++) 
        {
            chunk_t* chunk = &(game->chunk_manager.chunks[x + y*game->chunk_manager.height]);
            chunk->vbo = 0; // not loaded
            chunk->blocks = NULL; // not loaded

            // Read the chunk's offset and length
            assert(fread(&chunk->offset, sizeof(int), 1, manager_file)==1);
            assert(fread(&chunk->block_count, sizeof(int), 1, manager_file)==1);
            // printf("offset:%d block_count:%d\n", chunk->offset, chunk->block_count);
        }
    }

    fclose(manager_file);
    // fclose(chunk_file  );

}

void free_chunk_manager(game_t* game) 
{
    free_all_chunks(game);
    free(game->chunk_manager.chunks);
    fclose(game->chunk_manager.chunk_file);
    return;
}

void load_chunk(game_t* game, int x, int y)
{
    //if is loaded
    chunk_t* chunk = &game->chunk_manager.chunks[x + y*game->chunk_manager.width];
    if (chunk->blocks != 0)
    {
        printf("do not load loaded, please\n");
        return; //cause already loaded
    }
    //so its not loaded

    //now we have buffer
    chunk->blocks = calloc(chunk->block_count, sizeof(block_t));
    assert(chunk->blocks != 0);

    //lets read into it
    fseek(game->chunk_manager.chunk_file, chunk->offset, SEEK_SET);
    fread(chunk->blocks, sizeof(block_t), chunk->block_count, game->chunk_manager.chunk_file);

    glGenBuffers(1, &chunk->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, chunk->vbo);
    glBufferData(GL_ARRAY_BUFFER, chunk->block_count * sizeof(block_t), chunk->blocks, GL_STATIC_DRAW);

    int size;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    // printf(" chunk size is %d\n", size);
}

void free_chunk(game_t* game, int x, int y)
{
    //if is not loaded
    chunk_t* chunk = &game->chunk_manager.chunks[x + y*game->chunk_manager.width];
    if (chunk->blocks == 0)
    {
        printf("unloading not loaded chunk\n");
        return; //cause already unloaded
    }

    free(chunk->blocks);

    glDeleteBuffers(1, &chunk->vbo);
}

void load_all_chunks(game_t* game)
{
    for(int x=0; x < game->chunk_manager.width; x++)
    {
        for(int y=0; y < game->chunk_manager.height; y++)
        {
            load_chunk(game, x, y);
        }
    }
}

void free_all_chunks(game_t* game)
{
    for(int x=0; x < game->chunk_manager.width; x++)
    {
        for(int y=0; y < game->chunk_manager.height; y++)
        {
            free_chunk(game, x, y);
        }
    }
}