#include "cute_tiled.c"
// #include "../client/load/cute_tiled.h"
// #include "../client/map/chunk.h"
#include <stdio.h>

#define print(...) printf(__VA_ARGS__)

#define CHUNK_SIZE 8

// copy_chunk_to_chunkfile(int i, int j, FILE* chunkfile);
// copy_chunk_to_chunkmap (int i, int j, FILE* chunkmap );

int main()
{
    char* cute_map_file = "assets/map/map.tmj";

    FILE* chunk_file   = fopen("assets/map/chunk_file", "wb");
    FILE* manager_file = fopen("assets/map/chunk_manager", "wb");

    cute_tiled_map_t* cute_map = cute_tiled_load_map_from_file(cute_map_file, 0);
    int* data = cute_map->layers[0].data;
    int height, width, chunks_height, chunks_width, offset, tiles_in_chunk;
    float x, y, z, val;
    height   = cute_map->height;
    width = cute_map->width ;

    //understandable ceil
    chunks_height = height / CHUNK_SIZE;
    chunks_width  = width  / CHUNK_SIZE;
    if (height % CHUNK_SIZE > 0) chunks_height++;
    if (width  % CHUNK_SIZE > 0) chunks_width ++;
    print("%d \n", cute_map->layers[0].data_count);

    // for(int column = 0; column < width; column++)
    // {
    //     for(int line = 0; line < height; line++)
    //     {   
    //         if (data[line*width + column] == 0)
    //         {
    //             continue;
    //         }
    //         x = (float)column;
    //         y = (float)line;
    //         z = 0;
    //         // print("x %f y %f z %f\n", x, y, z);
    //         // print("data[line][column] %f\n", data[line*width + column]);
    //         print("%d ", data[line*width + column]);
    //     }
    //     print("\n");
    // }
    print("\nchunks_height %d chunks_width %d\n", chunks_height, chunks_width);
    assert(fwrite(&chunks_height, sizeof(int), 1, manager_file)==1);
    // fprintf(manager_file, "%d ", chunks_height);
    // int pos = ftell(manager_file);
    // fseek(manager_file, 0, SEEK_SET);
    // int test_height = -1;
    // assert(fread(&test_height, sizeof(int), 1, manager_file)==1);
    // printf("test_height %d\n\n", test_height);

    // fseek(manager_file, pos, SEEK_SET);

    assert(fwrite(&chunks_width , sizeof(int), 1, manager_file)==1);

    for (int chunk_line = 0; chunk_line < chunks_height; chunk_line++)
    {
        for (int chunk_column = 0; chunk_column < chunks_width; chunk_column++)
        {
            offset = ftell(chunk_file);
            tiles_in_chunk = 0;
            print("offset %d\n", offset);
            fwrite(&offset, sizeof(int), 1, manager_file);

            //for each layer
            for (cute_tiled_layer_t* layer = &cute_map->layers[0]; layer != NULL; layer = layer->next)
            {
                //copy chunk from current layer to chunkfile
                data = layer->data;
                for(int column = chunk_column*CHUNK_SIZE; column < (chunk_column + 1)*CHUNK_SIZE && column < width; column++)
                {
                    for(int line = chunk_line*CHUNK_SIZE; line < (chunk_line + 1)*CHUNK_SIZE && line < height; line++)
                    {   
                        if (data[line*width + column] == 0)
                        {
                            continue;
                        }
                        x = (float)column;
                        y = (float)line;
                        z = (float) (-(int)layer->offsety / 16);
                        val = (float)data[line*width + column] - 1;
                        // print("x %2.1f y %2.1f z %2.1f\n", x, y, z);
                        // print("data[line*width + column] %f\n", val);
                        fwrite(&x  , sizeof(float), 1, chunk_file);
                        fwrite(&y  , sizeof(float), 1, chunk_file);
                        fwrite(&z  , sizeof(float), 1, chunk_file);
                        fwrite(&val, sizeof(float), 1, chunk_file);
                        tiles_in_chunk++;
                    }
                }
            }
            print("tiles_in_chunk %d\n", tiles_in_chunk);
            fwrite(&tiles_in_chunk, sizeof(int), 1, manager_file);
        }
    }
    fclose(chunk_file);
    fclose(manager_file);

    cute_tiled_free_map(cute_map);

    // manager_file = fopen("assets/map/chunk_manager", "rb");

    // int temp = 66;
    // assert(fread(&temp, sizeof(int), 1, manager_file)==1);

    // fclose(manager_file);

    return 0;
}
