#include "vec.h"

vec2f v2add(vec2f a, vec2f b)
{
	vec2f res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return res;
}
vec2f v2sub(vec2f a, vec2f b)
{
	vec2f res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return res;
}
vec2f v2scale(vec2f v, float scale)
{
	vec2f res;
	res.x = v.x * scale;
	res.y = v.y * scale;
	return res;
}
float v2dot(vec2f a, vec2f b)
{
	float res;
	res += a.x * b.x;
	res += a.y * b.y;
	return res;
}

vec3f v3add(vec3f a, vec3f b)
{
	vec3f res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return res;
}
vec3f v3sub(vec3f a, vec3f b)
{
	vec3f res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return res;
}
vec3f v3scale(vec3f v, float scale)
{
	vec3f res;
	res.x = v.x * scale;
	res.y = v.y * scale;
	res.z = v.z * scale;
	return res;
}
float v3dot(vec3f a, vec3f b)
{
	float res;
	res += a.x * b.x;
	res += a.y * b.y;
	res += a.z * b.z;
	return res;
}


vec2d v2dscale(vec2d v, double scale)
{
	vec2d res;
	res.x = v.x * scale;
	res.y = v.y * scale;
	return res;
}
double v2ddot(vec2d a, vec2d b)
{
	double res;
	res += a.x * b.x;
	res += a.y * b.y;
	return res;
}
vec2d v2dnorm(vec2d v)
{
	double dotp = v2ddot(v, v);
	double scale = 1/sqrt(dotp);
	vec2d res = v2dscale(v, scale);
	return res;
}

vec3d v3dadd(vec3d a, vec3d b)
{
	vec3d res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return res;
}
vec3d v3dsub(vec3d a, vec3d b)
{
	vec3d res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return res;
}
vec3d v3dscale(vec3d v, double scale)
{
	vec3d res;
	res.x = v.x * scale;
	res.y = v.y * scale;
	res.z = v.z * scale;
	return res;
}
double v3ddot(vec3d a, vec3d b)
{
	double res;
	res += a.x * b.x;
	res += a.y * b.y;
	res += a.z * b.z;
	return res;
}
vec3d v3dnorm(vec3d v)
{
	double dotp = v3ddot(v, v);
    double scale;
    if (dotp == 0)
    {
        scale = 1.0;
    }
    else scale = 1/sqrt(dotp);
	vec3d res = v3dscale(v, scale);
	return res;
}
