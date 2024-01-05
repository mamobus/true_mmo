#include "cute_tiled.c"
// #include "../client/load/cute_tiled.h"
// #include "../client/map/chunk.h"
#include <stdio.h>
#include <math.h>

#define print(...) printf(__VA_ARGS__)

#define CHUNK_SIZE 16

// copy_chunk_to_chunkfile(int i, int j, FILE* chunkfile);
// copy_chunk_to_chunkmap (int i, int j, FILE* chunkmap );

//  X       Y      Z
int length, width, height;

float distance(int x, int y, int z, int x0, int y0, int z0)
{
    int dx, dy, dz;

    dx = abs(x - x0);
    dy = abs(y - y0);
    dz = abs(z - z0);

    if(dx > 0) dx -= 1;
    if(dy > 0) dy -= 1;
    if(dz > 0) dz -= 1;

    double dist2 = dx*dx + dy*dy + dz*dz;
    float dist = (float) sqrt(dist2);

    return dist;
}

float get_distance(float* voxels, int x0, int y0, int z0)
{
    float min_distance = 1000.0;

    for (int z = 0; z < height; z++)
    {
        for(int x = 0; x < length; x++)
        {
            for(int y = 0; y < width; y++)
            {   
                //for every block, if its not empty, check how far it is
                if (voxels[z * width*length + y * length + x] > -0.5)
                {
                    float dist = distance(x,y,z, x0,y0,z0);
                    if (dist < min_distance)
                    {
                        min_distance = dist;
                    }
                }

            }
        }
    }
    
    return min_distance;
}

int main()
{
    // char* cute_map_file = "assets/map/map.tmj";
    // char* cute_map_file = "assets/map/new_map.tmj";
    char* cute_map_file = "assets/map/rtmap1tmj.tmj";
    // char* cute_map_file = "assets/map/rtmap.tmj";


    FILE* rayworld_file   = fopen("assets/map/ray_file", "wb");
    FILE* chunk_file   = fopen("assets/map/chunk_file", "wb");
    FILE* manager_file = fopen("assets/map/chunk_manager", "wb");

    cute_tiled_map_t* cute_map = cute_tiled_load_map_from_file(cute_map_file, 0);
    int* data = cute_map->layers[0].data;
    int chunks_length, chunks_width, offset, tiles_in_chunk;
    float x, y, z, val;

    length   = cute_map->height;
    width = cute_map->width ;
    height = 0;
    cute_tiled_layer_t* curlayer = cute_map->layers;
    while(curlayer != NULL){
        height++;
        curlayer = curlayer->next;
    }
    // height = 16;
    //understandable ceil
    chunks_length = length / CHUNK_SIZE;
    chunks_width  = width  / CHUNK_SIZE;
    if (length % CHUNK_SIZE > 0) chunks_length++;
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
    print("\nchunks_length %d chunks_width %d\n", chunks_length, chunks_width);
    assert(fwrite(&chunks_length, sizeof(int), 1, manager_file)==1);
    assert(fwrite(&chunks_width , sizeof(int), 1, manager_file)==1);
    assert(fwrite(&length, sizeof(int), 1, rayworld_file)==1);
    assert(fwrite(&width , sizeof(int), 1, rayworld_file)==1);
    assert(fwrite(&height, sizeof(int), 1, rayworld_file)==1);
    // fprintf(manager_file, "%d ", chunks_length);
    // int pos = ftell(manager_file);
    // fseek(manager_file, 0, SEEK_SET);
    // int test_height = -1;
    // assert(fread(&test_height, sizeof(int), 1, manager_file)==1);
    // printf("test_height %d\n\n", test_height);

    // fseek(manager_file, pos, SEEK_SET);


    for (int chunk_column = 0; chunk_column < chunks_length; chunk_column++) //X
    {
        for (int chunk_line = 0; chunk_line < chunks_width; chunk_line++) //Y
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
                for(int xx = chunk_column*CHUNK_SIZE; xx < (chunk_column + 1)*CHUNK_SIZE && xx < length; xx++) //X
                {
                    for(int yy = chunk_line*CHUNK_SIZE; yy < (chunk_line + 1)*CHUNK_SIZE && yy < width; yy++) //Y
                    {   
                        if (data[yy*length + xx] != 0)
                        {
                            x = (float)xx;
                            y = (float)yy;
                            // z = (float) (-layer->offsety / 12.0);
                            z = (float) (-layer->offsety / 16.0);
                            val = (float)data[yy*length + xx] - 1;
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
            }
            print("tiles_in_chunk %d\n", tiles_in_chunk);
            assert(fwrite(&tiles_in_chunk, sizeof(int), 1, manager_file)==1);
        }
    }
    fclose(chunk_file);
    fclose(manager_file);

    float* blocks = calloc(height*width*length, sizeof(float));
    float* SDF    = calloc(height*width*length, sizeof(float));

    //not efficient order of operations but who cares
    int current_z = 0;
    for (cute_tiled_layer_t* layer = &cute_map->layers[0]; layer != NULL; layer = layer->next, current_z++)
    {
        //copy layer data from current layer to rayfile
        data = layer->data;
        for(int x = 0; x < length; x++)
        {
            for(int y = 0; y < width; y++)
            {   
                //but to rayfile write always
                float f_voxel = (float) (data[y*length + x] - 1);
                blocks[current_z * width*length + y*length + x] = f_voxel;
            }
        }
    }

    //so whole world is in grid. Lets calcute SDF!
    for (int z = 0; z < height; z++)
    {
        for(int y = 0; y < width; y++)
        {
            for(int x = 0; x < length; x++)
            {   
                //but to rayfile write always
                float f_sdf = (float) (0);
                f_sdf = get_distance(blocks, x,y,z);
                printf ("%.2f ", f_sdf);

                SDF[z * width*length + y*length + x] = f_sdf;
                // assert(fwrite(&f_sdf, sizeof(float), 1, rayworld_file)==1);
            }
            printf ("\n");
        }
        printf ("\n");

    }
    // printf("%d\n", height*width*length)
    assert(fwrite(blocks, sizeof(float), height*width*length, rayworld_file)==height*width*length);
    assert(fwrite(SDF   , sizeof(float), height*width*length, rayworld_file)==height*width*length);

    fclose(rayworld_file);
    cute_tiled_free_map(cute_map);

    // manager_file = fopen("assets/map/chunk_manager", "rb");

    // int temp = 66;
    // assert(fread(&temp, sizeof(int), 1, manager_file)==1);

    // fclose(manager_file);

    return 0;
}
