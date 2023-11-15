#include "update.h"

// #define shift_point(point, center, width, height, signx,signy,signz) \
// do{\
// point = center; \
// point.x = point.x signx width; \
// point.y = point.y signy width; \
// point.z = point.z signz height; \
// } while(0)

// #define create_cuboid(shape_dest, center, width, height) \
// do{\
// shift_point(shape_dest[0], center, width, height, +,+,+);\
// shift_point(shape_dest[1], center, width, height, +,-,+);\
// shift_point(shape_dest[2], center, width, height, -,+,+);\
// shift_point(shape_dest[3], center, width, height, -,-,+);\
// shift_point(shape_dest[4], center, width, height, +,+,-);\
// shift_point(shape_dest[5], center, width, height, +,-,-);\
// shift_point(shape_dest[6], center, width, height, -,+,-);\
// shift_point(shape_dest[7], center, width, height, -,-,-);\
// } while(0)


typedef struct collider_polyhedron_t
{
    int count;
    Vec3d* verticies;
} collider_polyhedron_t;

typedef struct collider_cube_t
{
    Vec3d center;
    double side;
} collider_cube_t;

typedef struct collider_multiple_cubes_t
{
    int count;
    collider_cube_t* cubes;
} collider_multiple_cubes_t;

typedef struct collider_sphere_t
{
    Vec3d center;
    double radius;
} collider_sphere_t;

typedef struct collider_ellipsoid_t 
{
    Vec3d center;
    double radius;
    double height_radius;
} collider_ellipsoid_t;

typedef struct collider_cylinder_t
{
    Vec3d center;
    double height;
    double radius;
} collider_cylinder_t;

double round_to1d(double x)
{
    // if (x < 0.0) return floorf(x);
    // else return ceilf(x);
    if (x > 0.0) return +1.0;
    else return -1.0;
}

void support_polyhedron(void* obj, ccd_vec3_t* dir, ccd_vec3_t* vec)
{
    struct collider_polyhedron_t* polyhedron = obj; 
    
    int imax = 0;
    double dmax = ccdVec3Dot(&polyhedron->verticies[0], dir);
    
    for (int i=1; i < polyhedron->count; i++) 
    {
        /* find vertex with max dot product in direction d */
        double dot = ccdVec3Dot(&polyhedron->verticies[i], dir);
        if (dot > dmax)
        {
            imax = i, dmax = dot;
        }
    } 
    ccdVec3Copy(vec, &polyhedron->verticies[imax]);
}
void support_cube(void* obj, ccd_vec3_t* dir, ccd_vec3_t* vec)
{
    struct collider_cube_t* cube = obj; 
    
    Vec3d direction;
    ccdVec3Copy(&direction, dir);
    ccdVec3Normalize(&direction);

    direction.x = round_to1d(direction.x);
    direction.y = round_to1d(direction.y);
    direction.z = round_to1d(direction.z);
    //so now direction is one of cube in 0,0,0 with 2.0 side verts
    //lets scale it to our cube
    ccdVec3Scale(&direction, cube->side/2.0);

    //now copy cube center + direction_scaled into *vec
    ccdVec3Copy(vec, &cube->center);
    ccdVec3Add (vec, &direction);
}   
void support_cylinder(void* obj, ccd_vec3_t* dir, ccd_vec3_t* vec)
{
    struct collider_cylinder_t* cylinder = obj; 
    
    Vec2d horizontal_dir;
    horizontal_dir.x = dir->v[0]; 
    horizontal_dir.y = dir->v[1];
    if(horizontal_dir.x == 0 && horizontal_dir.y == 0)
    {
        horizontal_dir = (Vec2d){1.0, 0};
    }
    ccdVec2Normalize(&horizontal_dir);

    horizontal_dir.x = round((horizontal_dir.x * 9.0)) / 9.0;
    horizontal_dir.y = round((horizontal_dir.y * 9.0)) / 9.0;

    double vertical_dir = round_to1d(dir->v[2]);

    ccdVec2Scale(&horizontal_dir, cylinder->radius);
    vertical_dir *= cylinder->height / 2.0;

    Vec3d direction;
    direction.x = horizontal_dir.x;
    direction.y = horizontal_dir.y;
    direction.z = vertical_dir;
    //now copy cube center + direction_scaled into *vec
    ccdVec3Copy(vec, &cylinder->center);
    ccdVec3Add (vec, &direction);
}   
void support_sphere(void* obj, ccd_vec3_t* dir, ccd_vec3_t* vec)
{   
    struct collider_sphere_t* sphere = obj; 

    Vec3d direction;
    ccdVec3Copy(&direction, dir);
    ccdVec3Normalize(&direction);

    // direction.x = round(direction.x*166.789) / 166.789;
    // direction.y = round(direction.y*166.789) / 166.789;
    // direction.z = round(direction.z*166.789) / 166.789;

    ccdVec3Copy(vec, &sphere->center);
    ccdVec3Scale(&direction, sphere->radius);
    ccdVec3Add(vec, &direction);
}
void support_ellipse(void* obj, ccd_vec3_t* dir, ccd_vec3_t* vec)
{   
    struct collider_ellipsoid_t* ellipse = obj; 

    Vec3d direction;
    ccdVec3Copy(&direction, dir);
    ccdVec3Normalize(&direction);

    // direction.x = round(direction.x*11.0) / 11.0;
    // direction.y = round(direction.y*11.0) / 11.0;
    // direction.z = round(direction.z*11.0) / 11.0;

    direction.x *= ellipse->radius;
    direction.y *= ellipse->radius;
    direction.z *= ellipse->height_radius / 2;

    ccdVec3Copy(vec, &ellipse->center);
    ccdVec3Add(vec, &direction);
}
void support_multiple_cubes(void* obj, ccd_vec3_t* dir, ccd_vec3_t* vec)
{
    collider_multiple_cubes_t* cubes = obj;

    int imax = 0;
    Vec3d current_vertex;
    support_cube(&cubes->cubes[0], dir, &current_vertex);

    double dot_max = ccdVec3Dot(&current_vertex, dir);
    for (int i=1; i < cubes->count; i++)
    {
        support_cube(&cubes->cubes[i], dir, &current_vertex);

        if (ccdVec3Dot(&current_vertex, dir) > dot_max)
        {
            dot_max = ccdVec3Dot(&current_vertex, dir);
            imax = i;
        }
    }

    support_cube(&cubes->cubes[imax], dir, &current_vertex);
    ccdVec3Copy(vec, &current_vertex);
}
//direction should be normalized

void update_player(game_t* game)
{
    double timestep = 0.01;
    double simulation_time_left = game->time_elapsed;
    while (simulation_time_left > timestep)
    {
        update_player_for_time(game, timestep);
        simulation_time_left -= timestep;
    }
    update_player_for_time(game, simulation_time_left);
}

void update_player_for_time(game_t* game, double time)
// void update_player(game_t* game)
{
    //so for now i dont care about accel

    //moved the plyaer by velocity
    Vec3d move = {0};
    ccdVec3Copy (&move, &game->player.vel);
    ccdVec3Scale(&move, time);
    ccdVec3Add(&game->player.pos, &move);
    // ccdVec3Scale(&move, game->time_elapsed);

    // then we reset accel cause that's how we handle it
    game->player.acl = (Vec3d){0,0,-5};

    // then handle accceleration 
    Vec3d speed_change = {0};
    ccdVec3Copy (&speed_change, &game->player.acl);
    ccdVec3Scale(&speed_change, time);
    ccdVec3Add(&game->player.vel, &speed_change);


    //handle input movement
    Vec3d input_vel = {0};
    ccdVec3Copy (&input_vel, &game->player.dir);
    ccdVec3Scale(&input_vel, 3);
    // ccdVec3Copy(&game->player.vel, &input_vel);
    game->player.vel.x = input_vel.x;
    game->player.vel.y = input_vel.y;
    // game->player.vel.z = -4.0;

    collider_cube_t block = {0};
    block.side = 1.0;
    // collider_sphere_t block = {0};
    // block.radius = 0.5;
    // collider_cube_t player_b = {0};
    // player_b.side = 1.0;

    collider_cylinder_t player = {0};
    player.center = game->player.pos;
    player.height = 2.0;
    player.radius = 0.33;

    // collider_ellipsoid_t player = {0};
    // player.center = game->player.pos;
    // player.height_radius = 2.0;
    // player.radius = 0.22;

    //now find blocks that it collides with
    //i should use chunks and subchunks but for now lets check ALL THE BLOCKS

    //so we do move it by 0.01 second at a time until wi reach real time
    //but later, for now skiP it

    //array for all block that player collides with 
    
    //for every chunk
    for(int i=0; i < game->chunk_manager.height*game->chunk_manager.width; i++)
    {
        //for every block
        for(int j=0; j < game->chunk_manager.chunks[i].block_count; j++)
        {
            
            block.center.x = (double)game->chunk_manager.chunks[i].blocks[j].pos.x;
            block.center.y = (double)game->chunk_manager.chunks[i].blocks[j].pos.y;
            block.center.z = (double)game->chunk_manager.chunks[i].blocks[j].pos.z;

            ccd_t ccd = {0};
            CCD_INIT(&ccd);

            ccd.support1 = support_cube;
            ccd.support2 = support_cylinder;
            ccd.max_iterations = 420;

            Vec3d separator = {0};
            //if player and block collide
            int res = ccdGJKSeparate(&block, &player, &ccd, &separator);
            assert(res != -2);
            assert(res == 0 || res == -1);


            if(res == 0) //if collide
            {
                //so if player is not too low in comparios with block than place it on top of the block
                //there might be diferent functions for different blocks
                //this is just for fullblock

                double height_diff;
                height_diff = (block.center.z + block.side/2) - (player.center.z - player.height/2);
                if(height_diff < 0.52 and height_diff > 0.0) //if player bottom is less or equal 0.51
                {
                    //then clearly should push player upwards

                    separator = (Vec3d){0,0,height_diff}; // then separator is just pushing player up
                }
                
                if(separator.x > 0.05 or separator.y > 0.05 or separator.z > 0.05)
                {
                    Vec3d parallel_speed = {0};
                    ccdVec3Copy(&parallel_speed, &separator);
                    ccdVec3Scale(&parallel_speed, (ccdVec3Dot(&separator, &game->player.vel) / ccdVec3Dot(&separator, &separator)));
                    ccdVec3Sub(&game->player.vel, &parallel_speed);
                    // game->player.vel.z = 0;
                }


                ccdVec3Add(&game->player.pos, &separator);   
                
                
                // if(separator.x != 0 and separator.y != 0 and separator.z != 0)
                // {
                //    f("SEP %.2f %.2f %.2f\n", separator.x, separator.y, separator.z);
                // }
                player.center = game->player.pos;
            }
        }
    }
}
