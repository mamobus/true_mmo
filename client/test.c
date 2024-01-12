// #include <ccd/ccd.h>
// #define USE_32BITS
// #include <vec.h>
#include <math.h>

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <time.h>

#include "../includes/sl_vec.h"

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


int main()
{
    // srand(3);
    // main_1();
    // main_2();
    // main_3();
    // main_2();

    // F(1, 1);
    // F(0, 1);
    // F(1, 0);
    // F(0.7, 0.7);
    // F(-0.7, -0.7);

    // TEST(a==a)
    // printf("%X %X", (0x2 | 0x30), (0x7 == 0x7 | 0x30));

    // for (int i=0; i < 2; i++)
    // {
        // printf("{");
        // for (int j=0; j < 2; j++)
        // {
            // printf("{");
            // for (int k=0; k < 2; k++)
            // {
            //     printf("{{%.2f, %.2f, %.2f}, {%.2f, %.2f, %.2f}, %.2f, %.2f}, ", rf(),rf(),rf(),  rf(),rf(),rf(),  rf(), rf());
            //     printf("vec3(%.2f, %.2f, %.2f)\n", rf(),rf(),rf());
            // }
            // printf("},\n");
        // }
        // printf("},\n");
    // }

    // printf("%e\n", 1024);
    // printf("%o\n", 1024);
    // printf("%a\n", 1024);
    // printf("%g\n", 1024);
    // printf("%h\n", 1024);
    // printf("%x\n", 0x123f);
    // printf("%X\n", -1073741819);
    // printf("%b\n", 0x123f);
    // printf("%n\n", 1024);

// #define print_vec2(vec) printf("%.1f : %.1f\n", vec.x, vec.y)
#define print_vec3(vec) printf("%.2f : %.2f : %.2f\n", vec.x, vec.y, vec.z)
#define print_vec4(vec) printf("%.2f : %.2f : %.2f : %.2f\n", vec.x, vec.y, vec.z, vec.w)

//     vec2 v;
    
//     v = _vec2_xy(1, 444);
//     print_vec2(v);
//     v = vec2(vec2(1.7, 444));
//     print_vec2(v);
//     v = vec2(vec2(vec2(1.7, 444)));
//     print_vec2(v);

    // test(v);
    // test(7);
    
    
    vec3 v3;
    // v3 = vec3(1,2,3);
    // print_vec3(v3);
    // print_vec3(v3);

    // int* p = &7;

    // #define maxint(a,b) ({int _a = (a), _b = (b); _a > _b ? _a : _b;})
    
    // const int one = 1;
    // v3 = vec3(1,2,3);
    v3 = vec3(ivec2(7.6, 3.2), ivec2(7777.7,666.99).x);



    // int a = ({int i; 
    // _Generic ((i),
    //     float : ({i=666;}),
    //     int : ({i=7;})
    // );
    // i;})
    // ;

    // v3 = vec3(one,vec2(one,one));
    // v3 = Ass(1,1,1);
    // int mx = maxint(1,2);
    print_vec3(v3);

    dvec4 v4;
    v4 = dvec4(1.77, vec3(2.5,1.5,77).yz, 666.55);
    dvec3 sv3 = dvec3(7,7,7);    
    
    print_vec4(v4);
    dvec3 v = v4.xyz;
    double val = mul(v, 1.0).x;
    printf("%.8f %.8f %.8f\n", val, length(cross(vec3(77,34,-3), vec3(99,6,6))));

}
