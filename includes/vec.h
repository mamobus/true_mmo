#pragma once

#include <math.h>

typedef union vec3d {
	 double m[3];
	 struct {
	 	double x, y, z;
	 };
} vec3d;

typedef union vec2d {
	 double m[2];
	 struct {
	 	double x, y;
	 };
} vec2d;


typedef union vec3f {
	 float m[3];
	 struct {
	 	float x, y, z;
	 };
} vec3f;

typedef union vec2f {
	 float m[2];
	 struct {
	 	float x, y;
	 };
} vec2f;


typedef struct vertex2 {
	vec2f pos;
	vec2f uv;
} vertex2;



vec2f v2add(vec2f a, vec2f b);
vec2f v2sub(vec2f a, vec2f b);
vec2f v2scale(vec2f v, float scale);
float v2dot(vec2f a, vec2f b);

vec3f v3add(vec3f a, vec3f b);
vec3f v3sub(vec3f a, vec3f b);
vec3f v3scale(vec3f v, float scale);
float v3dot(vec3f a, vec3f b);


vec2d v2dscale(vec2d v, double scale);
double v2ddot(vec2d a, vec2d b);
vec2d v2dnorm(vec2d v);

vec3d v3dadd(vec3d a, vec3d b);
vec3d v3dsub(vec3d a, vec3d b);
vec3d v3dscale(vec3d v, double scale);
double v3ddot(vec3d a, vec3d b);
vec3d v3dnorm(vec3d v);
vec3d v3dcross(vec3d a, vec3d b);