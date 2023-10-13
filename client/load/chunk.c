#include "chunk.h"

// #define PRINT printf("line %d, function %s\n", __LINE__, __FUNCTION__);

void load_chunk_manager(char* manager_file_name, char* chunk_file_name, chunk_manager_t* chunk_manager) 
{
    FILE* manager_file = fopen(manager_file_name, "rb");
    FILE* chunk_file   = fopen(chunk_file_name,   "rb");
    assert(manager_file != 0);
    assert(chunk_file != 0);

    chunk_manager->chunk_file = chunk_file;

    // Read the height and width of the 2D array of chunk_t objects from the file
    assert(fread(&chunk_manager->height, sizeof(int), 1, manager_file)==1);
    assert(fread(&chunk_manager->width , sizeof(int), 1, manager_file)==1);

    // Allocate memory for the height*width chunks
    chunk_manager->chunks = calloc(chunk_manager->height * chunk_manager->width, sizeof(chunk_t));
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
            assert(fread(&chunk->offset, sizeof(int), 1, manager_file)==1);
            assert(fread(&chunk->tile_count, sizeof(int), 1, manager_file)==1);
            printf("offset:%d tile_count:%d\n", chunk->offset, chunk->tile_count);
        }
    }

    fclose(manager_file);
    // fclose(chunk_file  );

}

void free_chunk_manager(chunk_manager_t* chunk_manager) 
{
    free_all_chunks(chunk_manager);
    free(chunk_manager->chunks);
    fclose(chunk_manager->chunk_file);
    return;
}

void load_chunk(chunk_manager_t* chunk_manager, int x, int y)
{
    //if is loaded
    chunk_t* chunk = &chunk_manager->chunks[x + y*chunk_manager->width];
    if (chunk->tiles != 0)
    {
        return; //cause already loaded
        printf("dont try to load loaded\n");
    }
    //so its not loaded
    //now we have buffer
    chunk->tiles = calloc(chunk->tile_count, sizeof(tile_t));
    void* calloced_memory = (void*)chunk->tiles;
    assert(calloced_memory != 0);
    //lets read into it
    fseek(chunk_manager->chunk_file, chunk->offset, SEEK_SET);
    fread(chunk->tiles, sizeof(tile_t), chunk->tile_count, chunk_manager->chunk_file);

    glGenBuffers(1, &chunk->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, chunk->vbo);
    glBufferData(GL_ARRAY_BUFFER, chunk->tile_count * sizeof(tile_t), chunk->tiles, GL_STATIC_DRAW);

    int size;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    printf("chunk size is %d\n", size);
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
    for(int y=0; y < chunk_manager->height; y++)
    {
        for(int x=0; x < chunk_manager->width; x++)
        {
            printf("trying to load chunk x%d y%d", x, y);
            load_chunk(chunk_manager, x, y);
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