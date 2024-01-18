// #include <ccd/ccd.h>
// #define USE_32BITS
// #include <vec.h>
#include <math.h>

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <time.h>

#include "../includes/sl_vec.h"

#define _printf_vec2d(prefix, specifier, vec) printf(specifier " " specifier "\n", (*((prefix##vec2*)(&vec))).x, (*((prefix##vec2*)(&vec))).y)
#define _printf_vec3d(prefix, specifier, vec) printf(specifier " " specifier " " specifier "\n", (*((prefix##vec3*)(&vec))).x, (*((prefix##vec3*)(&vec))).y, (*((prefix##vec3*)(&vec))).z)
#define _printf_vec4d(prefix, specifier, vec) printf(specifier " " specifier " " specifier " " specifier "\n", (*((prefix##vec4*)(&vec))).x, (*((prefix##vec4*)(&vec))).y, (*((prefix##vec4*)(&vec))).z, (*((prefix##vec4*)(&vec))).w)

#define printf_vec(vec) \
({typeof(vec) vec_copy = vec;\
_Generic((vec),\
   _ivec2 : _printf_vec2d(i, "%d", vec_copy),\
    ivec2 : _printf_vec2d(i, "%d", vec_copy),\
    ivec3 : _printf_vec3d(i, "%d", vec_copy),\
    ivec4 : _printf_vec4d(i, "%d", vec_copy),\
   _vec2  : _printf_vec2d( , "%.3f", vec_copy),\
    vec2  : _printf_vec2d( , "%.3f", vec_copy),\
    vec3  : _printf_vec3d( , "%.3f", vec_copy),\
    vec4  : _printf_vec4d( , "%.3f", vec_copy),\
   _dvec2 : _printf_vec2d(d, "%.3lf", vec_copy),\
    dvec2 : _printf_vec2d(d, "%.3lf", vec_copy),\
    dvec3 : _printf_vec3d(d, "%.3lf", vec_copy),\
    dvec4 : _printf_vec4d(d, "%.3lf", vec_copy),\
   _bvec2 : _printf_vec2d(b, "%d", vec_copy),\
    bvec2 : _printf_vec2d(b, "%d", vec_copy),\
    bvec3 : _printf_vec3d(b, "%d", vec_copy),\
    bvec4 : _printf_vec4d(b, "%d", vec_copy),\
    default : _create_type_error()\
);\
vec_copy;})

// #define shift_point(point, signx,signy,signz) \
// do{\
// point = pos; \
// point.x = point.x signx width; \
// point.y = point.y signy width; \
// point.z = point.z signz height; \
// } while(0)


// struct sphere
// {
//     vec3f center;
//     float radius;
// };
// struct cube
// {
//     vec3f center;
//     float side;
// };
// struct polyhedron
// {
//     int count;
//     vec3f* verticies;
// };

// typedef struct collider_cube_t
// {
//     vec3f center;
//     float side;
// } collider_cube_t;

// typedef struct collider_sphere_t
// {
//     vec3f center;
//     float radius;
// } collider_sphere_t;

// typedef struct collider_cylinder_t
// {
//     vec3f center;
//     float height;
//     float radius;
// } collider_cylinder_t;

// int cuboid_collide(vec3f center1, vec3f sides1, vec3f center2, vec3f sides2)
// {
//     // check if centers are closer than sides size.
//     for (int i=0; i < 3; i++)
//     {
//         float center_dist = fabsf(center1.m[i] - center2.m[i]);
//         float   side_dist = (sides1.m[i] + sides2.m[i]) / 2.0f;

//         if(center_dist < side_dist)
//         {
//             //collide
//             return 1;
//         }
//     }

//     // Otherwise, the cuboids dont collide.
//     return 0;
// }

// float round_to1f(float x)
// {
//     // if (x < 0.0) return floorf(x);
//     // else return ceilf(x);
//     if (x < 0.0) return -1.0;
//     else return 1.0;
// }

// void support_cube(void* obj, ccd_vec3_t* dir, ccd_vec3_t* vec)
// {
//     struct collider_cube_t* cube = obj; 
    
//     vec3f direction;
//     ccdVec3Copy(&direction, dir);
//     // if(direction.)
//     ccdVec3Normalize(&direction);

//     direction.x = round_to1f(direction.x);
//     direction.y = round_to1f(direction.y);
//     direction.z = round_to1f(direction.z);
//     //so now direction is one of cube in 0,0,0 with 2.0 side verts
//     //lets scale it to our cube
//     ccdVec3Scale(&direction, cube->side/2.0);

//     //now copy cube center + direction_scaled into *vec
//     ccdVec3Copy(vec, &cube->center);
//     ccdVec3Add (vec, &direction);
// }   
// void support_cylinder(void* obj, ccd_vec3_t* dir, ccd_vec3_t* vec)
// {
//     struct collider_cylinder_t* cylinder = obj; 
    
//     vec2f horizontal_dir;
//     horizontal_dir.x = dir->v[0]; 
//     horizontal_dir.y = dir->v[1];
//     // assert(horizontal_dir.x !=0.0);
//     // assert(horizontal_dir.y !=0.0);
//     if(horizontal_dir.x == 0 && horizontal_dir.y == 0)
//     {
//         horizontal_dir = (vec2f){1.0, 0};
//     }
//     ccdVec2Normalize(&horizontal_dir);

//     // horizontal_dir.x = roundf((horizontal_dir.x * 10.0)) / 10.0;
//     // horizontal_dir.y = roundf((horizontal_dir.y * 10.0)) / 10.0;
//     float vertical_dir = round_to1f(dir->v[2]);

//     ccdVec2Scale(&horizontal_dir, cylinder->radius);
//     vertical_dir *= cylinder->height / 2.0;

//     vec3f direction;
//     direction.x = horizontal_dir.x;
//     direction.y = horizontal_dir.y;
//     direction.z = vertical_dir;
//     //now copy cube center + direction_scaled into *vec
//     ccdVec3Copy(vec, &cylinder->center);
//     ccdVec3Add (vec, &direction);
// }   


// void support_sphere(void* obj, ccd_vec3_t* dir, ccd_vec3_t* vec)
// {   
//     struct sphere* sphere = obj; 

//     vec3f direction;
//     ccdVec3Copy(&direction, dir);
//     ccdVec3Normalize(&direction);

//     ccdVec3Copy(vec, &sphere->center);
//     ccdVec3Scale(&direction, sphere->radius);
//     ccdVec3Add(vec, &direction);
// }

// void support_polyhedron(void* obj, ccd_vec3_t* dir, ccd_vec3_t* vec)
// {
//     struct polyhedron* polyhedron = obj; 
    
//     int imax = 0;
//     float dmax = ccdVec3Dot(&polyhedron->verticies[0], dir);
    

//     for (int i=1; i < polyhedron->count; i++) 
//     {
//         /* find vertex with max dot product in direction d */
//         float dot = ccdVec3Dot(&polyhedron->verticies[i], dir);
//         if (dot > dmax)
//         {
//             imax = i, dmax = dot;
//         }
//     } 
//     ccdVec3Copy(vec, &polyhedron->verticies[imax]);
// }


// int main_1()
// {
//     struct sphere sphere1 = {0};
//     vec3f center = {1.6, 0.5, 0.5};
//     sphere1.center = center;
//     sphere1.radius = 1.0;

//     float verts2[] = {
//         +0.0, +0.0, +0.0,
//         +1.0, +0.0, +0.0,
//         +0.0, +1.0, +0.0,
//         +1.0, +1.0, +0.0,

//         +0.0, +0.0, +1.0,
//         +1.0, +0.0, +1.0,
//         +0.0, +1.0, +1.0,
//         +1.0, +1.0, +1.0,
//     };
//     struct polyhedron polyhedron2 = {8, &verts2};


//     ccd_t ccd;
//     CCD_INIT(&ccd);

//     ccd.support1 = support_sphere;
//     ccd.support2 = support_polyhedron;

//     ccd.max_iterations = 42;
//     int res = 0;
//     int ITER = 100000;
//     float start = (float)clock()/CLOCKS_PER_SEC;
//     vec3f dir, sep;

//     res = ccdGJKSeparate(&sphere1, &polyhedron2, &ccd, &sep);


//     // for (int i=0; i<ITER; i++)
//     // {
//     //     // res = ccdGJKIntersect(&polyhedron1, &polyhedron2, &ccd);
//     //     res = ccdGJKSeparate(&sphere1, &polyhedron2, &ccd, &sep);
//     // }
//     // float time = (float)clock()/CLOCKS_PER_SEC - start;
    
//     // printf("intersect %d time %f depth %f\n", res, (time / ITER)*1000000 , depth);
//     // printf("intersect %d time %f\n", res, (time / ITER)*1000000);
//     printf("sep %f %f %f\n", sep.x, sep.y, sep.z);
//     // printf("dir %f %f %f\n", dir.x, dir.y, dir.z);
//     // printf("pos %f %f %f\n", pos.x, pos.y, pos.z);
// }

// float round_away_from_zero(float x)
// {
//     // if (x < 0.0) return floorf(x);
//     // else return ceilf(x);
//     if (x < 0.0) return -1.0;
//     else return 1.0;
// }

// int main_2()
// {
//     struct collider_cube_t cube;
//     cube.center = (vec3f){0.0,0.0,4.0};
//     cube.side = 1.0;
//     // struct collider_cube_t cube2;
//     // cube2.center = (vec3f){0,0,0};
//     // cube2.side = 2.0;
//     struct collider_cylinder_t cylinder;
//     cylinder.center = (vec3f){0.0,0.0,4.75};
//     cylinder.height = 2.0;
//     cylinder.radius = 0.5;
//     struct collider_cylinder_t cylinder2;

//     ccd_t ccd;
//     CCD_INIT(&ccd);
//     // ccd.epa_tolerance  = 0.01;
//     // ccd.mpr_tolerance  = 0.01;
//     // ccd.dist_tolerance = 0.01;

//     // ccd.support1 = support_cube;
//     ccd.support1 = support_cube;
//     // ccd.support2 = support_cylinder;
//     ccd.support2 = support_cylinder;

//     ccd.max_iterations = 420;
//     int res = 0;
//     // int ITER = 100000;
//     int ITER = 100000;
//     float start = (float)clock()/CLOCKS_PER_SEC;
//     vec3f sep = {0};
//     // double a;
//     // float b = 0.0;
//     // int bi = 4234;
//     for (int i=0; i<ITER; i++)
//     {
//         // res = ccdGJKIntersect(&cylinder, &cylinder, &ccd);
//         res = ccdGJKSeparate(&cube, &cylinder, &ccd, &sep);
//         // a = (double) bi;
//         // res = ccdGJKPenetration(&cube, &cylinder, &ccd, &depth, &dir, &pos);
//         // assert(res!=-2);
//     }
//     float time = (float)clock()/CLOCKS_PER_SEC - start;
    
//     // printf("intersect %d time %f depth %f\n", res, (time / ITER)*1000000 , depth);
//     printf("intersect %d time %f\n", res, (time / ITER)*1000000);
//     printf("sep %f %f %f\n", sep.x, sep.y, sep.z);
//     // printf("dir %f %f %f\n", dir.x, dir.y, dir.z);
//     // printf("pos %f %f %f\n", pos.x, pos.y, pos.z);
// }

#define PI 3.14159265358979323846
int f(double x, double y)
{
    double angle = atan2(y, x);
    // double angle = atan2(y, x) + PI;
    int steps = ((int)round(angle / (PI / 4)) % 8);
    if (steps < 0) steps += 8;
    return steps;
}

#define F(x, y) printf("%d <= %0.2lf %0.2lf\n", f(x, y), (double)x, (double)y)

// #define TEST(x) printf(##x); x;

// struct vec3
// {
//     float x,y,z;
// };

// struct material
// {
//     struct vec3 emmitance;   //for each color
//     struct vec3 reflectance; //for each color
//     float roughness;
//     float opacity;
// };

// struct block_t
// {
// 	struct material mat;
// };

// float rf()
// {
//     return ((float) rand()) / RAND_MAX;
// }

// #include "entity.h"
// #include "../includes/flecs/flecs.c"
#include "../includes/flecs/flecs.h"

typedef struct physics_component{
    dvec3 pos;
    dvec3 vel;
} physics_component;

typedef struct tag_player tag_player;
typedef struct tag_npc tag_npc;
typedef struct tag_monster tag_monster;
typedef struct tag_boss tag_boss;

int main()
{
    ecs_world_t* world = ecs_init();

    ECS_COMPONENT(world, physics_component);

    
    
    ECS_TAG(world, tag_player);
    ECS_TAG(world, tag_npc);
    ECS_TAG(world, tag_monster);
    ECS_TAG(world, tag_boss);


    ecs_entity_t e1 = ecs_new_id(world);
    ecs_set(world, e1, physics_component, {dvec3(1,1,1), dvec3(2,2,2)});
    // const physics_component* pc = ecs_get(world, e1, physics_component);

    ecs_entity_t e2 = ecs_new_id(world);
    ecs_set(world, e2, physics_component, {dvec3(6,6,6), dvec3(7,7,7)});
    ecs_add(world, e2, tag_npc);
    ecs_entity_t e3 = ecs_new_id(world);
    ecs_set(world, e3, physics_component, {dvec3(1,1,2), dvec3(2,2,2)});
    ecs_add(world, e3, tag_npc);
    ecs_add(world, e3, tag_player);

    // const physics_component* pc = ecs_get(world, e2, physics_component);

    // printf("%d\n", e1);
    // printf("%d\n", e2);
    printf("%d\n", ecs_id(physics_component));
    // printf("%d\n", ecs_id(tag_player));
    // printf("%d\n", ecs_id(tag_npc));
    // printf("%d\n", ecs_id(tag_monster));
    // printf("%d\n", ecs_id(tag_boss));

    ecs_query_t* qry = ecs_query_init(world, &(ecs_query_desc_t) {
        .filter.terms = {
            {.id = ecs_id(physics_component)},
            {.id = ecs_id(tag_npc)}
        }
    });

    ecs_iter_t it = ecs_query_iter(world, qry);
    while(ecs_query_next(&it))
    {
        physics_component* pcs = ecs_field(&it, physics_component, 1);

        for (int i = 0; i < it.count; i ++) {
            printf_vec(pcs[i].pos);
    }
    }

    // printf_vec(pc->pos);
    // printf_vec(pc->vel);
    

    
    // srand(3);
    // main_1();
    // main_2();
    // main_3();
    // main_2();
}
