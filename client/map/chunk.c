#include "chunk.h"

//load chunks one by one into vbos and calloced memory. Use SQL to manage chunks in file
void create_shunk_system(chunk_system_t* chunk_system)
{
    chunk_system->draw_chunks = calloc(25, sizeof(chunk_draw_t));
    load_map_from_file("", &chunk_system->map);
}

void load_chunk(chunk_draw_t* chunk, int chunk_x, int chunk_y)
{
}

void free_chunk(chunk_draw_t* chunk)
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

//on chunk_cross
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
 