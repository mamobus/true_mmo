#include "chunk.h"

//load chunks one by one into vbos and calloced memory. Use SQL to manage chunks in file
chunk_system_t create_shunk_system()
{
    chunk_system_t chunk_system;
    chunk_system.chunk_count = 0;
    chunk_system.current_x = 0;
    chunk_system.current_y = 0;
    // chunk_system.chunks = calloc(chunk_system.max, sizeof(chunk_t));
    chunk_system.chunks = calloc(49, sizeof(chunk_t)); //current
    //load surrounding chunks

    return chunk_system;
}

void load_chunk(chunk_t* chunk, int chunk_x, int chunk_y)
{
}

void free_chunk(chunk_t* chunk)
{
}

is_chunk_too_far_away(int chunk_x, int chunk_y, float player_x, float player_y)
{
    int player_chunk_x = ((int) player_x) / 8;
    int player_chunk_y = ((int) player_y) / 8;

    if(abs(player_chunk_x - chunk_x) > 2 || abs(player_chunk_y - chunk_y) > 2)
    {
        return 1;
    }
}

void handle_shunk_system(chunk_system_t* chunk_system, player_t player)
{
    for (int i = 0; i < chunk_system->chunk_count; i++)
    {
        if(is_chunk_too_far_away(chunk_system->chunks[i].x, chunk_system->chunks[i].y, player.x, player.y))
        {
            free_chunk(&chunk_system->chunks[i]);
        }
    }
}
