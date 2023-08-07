#include "chunk.h"

//load chunks one by one into vbos and calloced memory. Use SQL to manage chunks in file
chunk_system_t* create_shunk_system()
{
    chunk_system_t chunk_system;
    // chunk_system.chunks = calloc(chunk_system.max, sizeof(chunk_t));
    chunk_system.chunks = calloc(24, sizeof(chunk_t)); //current
    //load surrounding chunks
}

void load_map_to_chunks(chunk_system_t* chunk_system)
{
    //calculate chunk xy\s and load_chunk them into chunk_system

}

chunk_t load_chunk_from_sql(int x, int y)
{
    //get chunk data and chunk tile_count
}

void load_chunk(chunk_system_t* chunk_system, int chunk_x, int chunk_y, int chunk_num)
{
    int x, y;
    //load chunk from sql
    chunk_t new_chunk = load_chunk_from_sql(x, y);

    chunk_system->chunks[chunk_num] = new_chunk;
}

void free_chunk(chunk_system_t* chunk_system, int chunk_x, int chunk_y, int chunk_num)
{
    //TODO clear on release but im not shure
    assert(chunk_system->chunks[chunk_num].data != 0);
    
    free(chunk_system->chunks[chunk_num].data);
    chunk_system->chunks[chunk_num].tile_count = 0;
}

void handle_shunk_system(chunk_system_t* chunk_system)
{
    //if moved enough then unload chunks behind and load chunks in front using load_&free_chunk
}
