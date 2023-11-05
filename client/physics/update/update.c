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
    Vec3* verticies;
} collider_polyhedron_t;

typedef struct collider_cube_t
{
    Vec3 center;
    float side;
} collider_cube_t;

typedef struct collider_sphere_t
{
    Vec3 center;
    float radius;
} collider_sphere_t;

typedef struct collider_cylinder_t
{
    Vec3 center;
    float height;
    float radius;
} collider_cylinder_t;

float round_to1f(float x)
{
    // if (x < 0.0) return floorf(x);
    // else return ceilf(x);
    if (x < 0.0) return -1.0;
    else return 1.0;
}

void support_polyhedron(void* obj, ccd_vec3_t* dir, ccd_vec3_t* vec)
{
    struct collider_polyhedron_t* polyhedron = obj; 
    
    int imax = 0;
    float dmax = ccdVec3Dot(&polyhedron->verticies[0], dir);
    
    for (int i=1; i < polyhedron->count; i++) 
    {
        /* find vertex with max dot product in direction d */
        float dot = ccdVec3Dot(&polyhedron->verticies[i], dir);
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
    
    Vec3 direction;
    ccdVec3Copy(&direction, dir);
    ccdVec3Normalize(&direction);

    direction.x = round_to1f(direction.x);
    direction.y = round_to1f(direction.y);
    direction.z = round_to1f(direction.z);
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
    
    Vec2 horizontal_dir;
    horizontal_dir.x = dir->v[0]; 
    horizontal_dir.y = dir->v[1];
    if(horizontal_dir.x == 0 && horizontal_dir.y == 0)
    {
        horizontal_dir = (Vec2){1.0, 0};
    }
    ccdVec2Normalize(&horizontal_dir);

    // horizontal_dir.x = roundf((horizontal_dir.x * 10.0)) / 10.0;
    // horizontal_dir.y = roundf((horizontal_dir.y * 10.0)) / 10.0;

    float vertical_dir = round_to1f(dir->v[2]);

    ccdVec2Scale(&horizontal_dir, cylinder->radius);
    vertical_dir *= cylinder->height / 2.0;

    Vec3 direction;
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

    Vec3 direction;
    ccdVec3Copy(&direction, dir);
    ccdVec3Normalize(&direction);

    direction.x = roundf(direction.x*6.789) / 6.789;
    direction.y = roundf(direction.y*6.789) / 6.789;
    direction.z = roundf(direction.z*6.789) / 6.789;

    ccdVec3Copy(vec, &sphere->center);
    ccdVec3Scale(&direction, sphere->radius);
    ccdVec3Add(vec, &direction);
}

//direction should be normalized
void update_player(game_t* game)
{
    //so for now i dont care about accel

    Vec3 move = {0};
    ccdVec3Copy (&move, &game->player.vel);
    ccdVec3Scale(&move, game->time_elapsed);
    ccdVec3Add(&game->player.pos, &move);
    //moved the plyaer by velocity

    //then handle accceleration
    Vec3 speed_change = {0};
    ccdVec3Copy (&speed_change, &game->player.acl);
    ccdVec3Scale(&speed_change, game->time_elapsed);
    ccdVec3Add(&game->player.vel, &speed_change);

    // then we reser accel cause that's how we handle it
    game->player.acl = (Vec3){0,0,-1.81};

    //handle input movement
    Vec3 input_accel = {0};
    ccdVec3Copy (&input_accel, &game->player.dir);
    ccdVec3Scale(&input_accel, game->time_elapsed*100);
    ccdVec3Add(&game->player.acl, &input_accel);

    //but wirhout some Resistive force it does not work, so we handle it
    Vec3 Resistive_acl = {0};
    ccdVec3Copy (&Resistive_acl, &game->player.vel);
    ccdVec3Normalize(&Resistive_acl);
    // float resist_koef = 0.7
    // ccdVec3Scale(&Resistive_acl, (-resist_koef) * ccdVec3Len2(&game->player.vel));
    // ccdVec3Scale(&Resistive_acl, -ccdVec3Len2(&game->player.vel)*ccdVec3Len2(&game->player.vel));
    // ccdVec3Add(&game->player.acl, &Resistive_acl);  
    // printf("%d\n", __LINE__);

    collider_cube_t block = {0};
    block.side = 1.0;
    // collider_sphere_t block = {0};
    // block.radius = 0.5;
    // collider_cube_t player_b = {0};
    // player_b.side = 1.0;

    collider_cylinder_t player = {0};
    player.center = game->player.pos;
    player.height = 3.0;
    player.radius = 0.25;

    //now find blocks that it collides with
    //i should use chunks and subchunks but for now lets check ALL THE BLOCKS

    //so we do move it by 0.01 second at a time until wi reach real time
    //but later, for now skiP it

    //starting player shape, may change 

    //for every chunk
    for(int i=0; i < game->chunk_manager.height*game->chunk_manager.width; i++)
    {
        //for every block
        for(int j=0; j < game->chunk_manager.chunks[i].block_count; j++)
        {
            block.center = game->chunk_manager.chunks[i].blocks[j].pos;

            ccd_t ccd = {0};
            CCD_INIT(&ccd);

            ccd.support1 = support_cube;
            ccd.support2 = support_cylinder;
            ccd.max_iterations = 42;

            Vec3 separator = {0};
            player.center = game->player.pos;
            //if player and block collide
            int res = ccdGJKSeparate(&block, &player, &ccd, &separator);
            assert(res != -2);
            assert(res == 0 || res == -1);
            if(res == 0)
            {
                Vec3 face_dir = {0};
                Vec3 block2player_line = {0};
                ccdVec3Copy(&block2player_line, &game->player.pos);
                ccdVec3Sub (&block2player_line, &block.center);


                int max_axis = 0;
                float max_axis_v = 0;

                for (int i=0; i < 3; i++)
                {
                    if (abs(block2player_line.m[i]) > max_axis_v)
                    {
                        max_axis_v = abs(block2player_line.m[i]);
                        max_axis = i;
                    }
                }
                face_dir.m[max_axis] = round_to1f(block2player_line.m[max_axis]);

                Vec3 vel_perpendicular;
                Vec3 vel_parallel;

                ccdVec3Copy (&vel_perpendicular, &face_dir);
                ccdVec3Scale(&vel_perpendicular, ccdVec3Dot(&face_dir, &game->player.vel)); // vel_perp = (vel, face) * face

                ccdVec3Copy(&vel_parallel, &game->player.vel);
                ccdVec3Sub(&vel_parallel, &vel_perpendicular); //now vel_parallel is here

                ccdVec3Copy(&game->player.vel, &vel_parallel);

                assert (fabsf(face_dir.x + face_dir.y + face_dir.z) < 1.5);

                ccdVec3Add(&game->player.pos, &separator);   
            }
        }
    }
}