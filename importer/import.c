#include "../client/map/cute_tiled.c"
#include "../client/map/chunk.c"
#include <stdio.h>

#define CHUNK_SIZE 8

copy_chunk_to_chunkfile(int i, int j, FILE* chunkfile);
copy_chunk_to_chunkmap (int i, int j, FILE* chunkmap );

int main()
{
    char* cute_map_file = "assets/map/map.tmj";

    FILE* chunk_file         = fopen("assets/map/chunk_file", "wb");
    FILE* chunk_manager_file = fopen("assets/map/chunk_manager", "wb");

    cute_tiled_map_t* cute_map = cute_tiled_load_map_from_file(cute_map_file, 0);
    int** data = cute_map->layers[0].data;
    int height, width, chunks_height, chunks_width, offset, tiles_in_chunk;
    float x, y, z;
    height   = cute_map->height;
    width = cute_map->width ;

    //understandable ceil
    chunks_height = height / CHUNK_SIZE;
    chunks_width  = width  / CHUNK_SIZE;
    if (height % CHUNK_SIZE > 0) chunks_height++;
    if (width  % CHUNK_SIZE > 0) chunks_width ++;

    fwrite(&chunks_height, sizeof(int), 1, chunk_manager_file);
    fwrite(&chunks_width , sizeof(int), 1, chunk_manager_file);

    printf("height %d height_in_chunks %d width %d width_in_chunks %d\n", height, chunks_height, width, chunks_width); //for debug

    for (int chunk_line = 0; chunk_line < chunks_height; chunk_line++)
    {
        for (int chunk_column = 0; chunk_column < chunks_width; chunk_column++)
        {
            //for each layer
            //copy chunk to chunkfile
            offset = ftell(chunk_file);
            tiles_in_chunk = 0;
            fwrite(&offset, sizeof(int), 1, chunk_manager_file);

            for(int line = chunk_line*CHUNK_SIZE; line < (chunk_line + 1)*CHUNK_SIZE && line < height; line++)
            {
                for(int column = chunk_column*CHUNK_SIZE; column < (chunk_column + 1)*CHUNK_SIZE && column < width; column++)
                {   
                    if (data[line][column] == 0)
                    {
                        continue;
                    }
                    x = (float)column;
                    y = (float)line;
                    z = 0;
                    fwrite(&x, sizeof(float), 1, chunk_file);
                    fwrite(&y, sizeof(float), 1, chunk_file);
                    fwrite(&z, sizeof(float), 1, chunk_file);
                    fwrite(&data[line][column], sizeof(float), 1, chunk_file);
                    tiles_in_chunk++;
                }
            }
            
            fwrite(&tiles_in_chunk, sizeof(int), 1, chunk_manager_file);
            
            // copy chunk to chunkmap
        }
    }
    fclose(chunk_file);
    fclose(chunk_manager_file);
}
