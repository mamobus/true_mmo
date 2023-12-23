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
    vec3d* verticies;
} collider_polyhedron_t;

typedef struct collider_cube_t
{
    vec3d center;
    double side;
} collider_cube_t;

typedef struct collider_multiple_cubes_t
{
    int count;
    collider_cube_t* cubes;
} collider_multiple_cubes_t;

typedef struct collider_sphere_t
{
    vec3d center;
    double radius;
} collider_sphere_t;

typedef struct collider_ellipsoid_t 
{
    vec3d center;
    double radius;
    double height_radius;
} collider_ellipsoid_t;

typedef struct collider_cylinder_t
{
    vec3d center;
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

void support_polyhedron(void* obj, vec3d* dir, vec3d* vec)
{
    struct collider_polyhedron_t* polyhedron = obj; 
    
    int imax = 0;
    double dmax = v3ddot(polyhedron->verticies[0], *dir);
    
    for (int i=1; i < polyhedron->count; i++) 
    {
        /* find vertex with max dot product in direction d */
        double dot = v3ddot(polyhedron->verticies[i], *dir);
        if (dot > dmax)
        {
            imax = i, dmax = dot;
        }
    } 
    *vec = polyhedron->verticies[imax];
}
void support_cube(void* obj, vec3d* dir, vec3d* vec)
{
    struct collider_cube_t* cube = obj; 
    
    vec3d direction = *dir;
    direction = v3dnorm(direction);

    direction.x = round_to1d(direction.x);
    direction.y = round_to1d(direction.y);
    direction.z = round_to1d(direction.z);
    //so now direction is one of cube in 0,0,0 with 2.0 side verts
    //lets scale it to our cube
    direction = v3dscale(direction, cube->side/2);

    //now copy cube center + direction_scaled into *vec
    *vec = v3dadd(cube->center, direction);
}   
void support_cylinder(void* obj, vec3d* dir, vec3d* vec)
{
    struct collider_cylinder_t* cylinder = obj; 
    
    vec2d horizontal_dir;
    horizontal_dir.x = dir->x; 
    horizontal_dir.y = dir->y;
    if(horizontal_dir.x == 0 && horizontal_dir.y == 0)
    {
        horizontal_dir = (vec2d){1.0, 0};
    }
    horizontal_dir = v2dnorm(horizontal_dir);

    horizontal_dir.x = round((horizontal_dir.x * 11.81)) / 11.81;
    horizontal_dir.y = round((horizontal_dir.y * 11.81)) / 11.81;

    double vertical_dir = round_to1d(dir->z);

    horizontal_dir = v2dscale(horizontal_dir, cylinder->radius);
    vertical_dir *= cylinder->height / 2.0;

    vec3d direction;
    direction.x = horizontal_dir.x;
    direction.y = horizontal_dir.y;
    direction.z = vertical_dir;
    //now copy cube center + direction_scaled into *vec
    *vec = v3dadd(cylinder->center, direction);
}  
void support_sphere(void* obj, vec3d* dir, vec3d* vec)
{   
    struct collider_sphere_t* sphere = obj; 

    vec3d direction = v3dnorm(*dir);

    // direction.x = round(direction.x*166.789) / 166.789;
    // direction.y = round(direction.y*166.789) / 166.789;
    // direction.z = round(direction.z*166.789) / 166.789;

    //vec = Dir*R+Center
    *vec = v3dadd(sphere->center, v3dscale(direction, sphere->radius));
}
void support_ellipse(void* obj, vec3d* dir, vec3d* vec)
{   
    struct collider_ellipsoid_t* ellipse = obj; 

    vec3d direction = v3dnorm(*dir);

    // direction.x = round(direction.x*11.0) / 11.0;
    // direction.y = round(direction.y*11.0) / 11.0;
    // direction.z = round(direction.z*11.0) / 11.0;

    direction.x *= ellipse->radius;
    direction.y *= ellipse->radius;
    direction.z *= ellipse->height_radius / 2;

    *vec = v3dadd(ellipse->center, direction);
}
void support_multiple_cubes(void* obj, vec3d* dir, vec3d* vec)
{
    collider_multiple_cubes_t* cubes = obj;

    int imax = 0;
    vec3d current_vertex;
    support_cube(&cubes->cubes[0], dir, &current_vertex);

    double dot_max = v3ddot(current_vertex, *dir);
    for (int i=1; i < cubes->count; i++)
    {
        support_cube(&cubes->cubes[i], dir, &current_vertex);

        if (v3ddot(current_vertex, *dir) > dot_max)
        {
            dot_max = v3ddot(current_vertex, *dir);
            imax = i;
        }
    }

    support_cube(&cubes->cubes[imax], dir, &current_vertex);
    *vec = current_vertex;
}
//direction should be normalized

void update_player_for_time(game_t* game, double time)
// void update_player(game_t* game)
{
    //so for now i dont care about accel

    //moved the plyaer by velocity
    vec3d pos_change = v3dscale(game->player.vel, time);
    game->player.pos = v3dadd(game->player.pos, pos_change);

    // then we reset accel cause that's how we handle it
    game->player.acl = (vec3d){0,0,-9.81};

    // then handle accceleration 
    vec3d speed_change = v3dscale(game->player.acl, time);
    game->player.vel = v3dadd(game->player.vel, speed_change);


    //handle input movement
    vec3d input_vel = v3dscale(game->player.dir, 3);
    // ccdVec3Copy (&input_vel, &game->player.dir);
    // ccdVec3Scale(&input_vel, 3);
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
            
            ccd.support1 = (void*)support_cube;
            ccd.support2 = (void*)support_cylinder;
            ccd.max_iterations = 42;

            vec3d separator = {0};
            //if player and block collide
// print
            int res = ccdGJKSeparate(&block, &player, &ccd, (ccd_vec3_t*)(&separator));
// print
            assert(res != -2);
            assert(res == 0 || res == -1);


            if(res == 0) //if collide
            {
// print
                //so if player is not too low in comparios with block than place it on top of the block
                //there might be diferent functions for different blocks
                //this is just for fullblock

                double height_diff;
                height_diff = (block.center.z + block.side/2) - (player.center.z - player.height/2);
                if(height_diff < 0.52 and height_diff > 0.0) //if player bottom is less or equal 0.51
                {
                    //then clearly should push player upwards

                    separator = (vec3d){0,0,height_diff}; // then separator is just pushing player up
                }
                
                if(separator.x > 0.05 or separator.y > 0.05 or separator.z > 0.05)
                {
                    vec3d parallel_speed;
                    parallel_speed = v3dscale(separator, (v3ddot(separator, game->player.vel) / v3ddot(separator, separator)));
                    game->player.vel = v3dsub(game->player.vel, parallel_speed);
                    // game->player.vel.z = 0;
                }

// print

                // ccdVec3Add(&game->player.pos, &separator);
                game->player.pos = v3dadd(game->player.pos, separator);                
                
                // if(separator.x != 0 and separator.y != 0 and separator.z != 0)
                // {
                //    f("SEP %.2f %.2f %.2f\n", separator.x, separator.y, separator.z);
                // }
                player.center = game->player.pos;
// print
            }
        }
    }
}

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