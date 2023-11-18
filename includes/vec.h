#pragma once

typedef union Vec3d {
	 double m[3];
	 struct {
	 	double x, y, z;
	 };
} Vec3d;

typedef union Vec2d {
	 double m[2];
	 struct {
	 	double x, y;
	 };
} Vec2d;


typedef union Vec3f {
	 float m[3];
	 struct {
	 	float x, y, z;
	 };
} Vec3f;

typedef union Vec2f {
	 float m[2];
	 struct {
	 	float x, y;
	 };
} Vec2f;


typedef struct Vertex2 {
	Vec2f pos;
	Vec2f uv;
} Vertex2;

inline Vec2f vec2addf(Vec2f a, Vec2f b)
{
	Vec2f res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return res;
}
inline Vec2f vec2subf(Vec2f a, Vec2f b)
{
	Vec2f res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return res;
}
inline Vec2f vec2scale(Vec2f v, float scale)
{
	Vec2f res;
	res.x = v.x * scale;
	res.y = v.y * scale;
	return res;
}

inline Vec3f vec3addf(Vec3f a, Vec3f b)
{
	Vec3f res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return res;
}
inline Vec3f vec3subf(Vec3f a, Vec3f b)
{
	Vec3f res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return res;
}

inline Vec3f vec3scale(Vec3f v, float scale)
{
	Vec3f res;
	res.x = v.x * scale;
	res.y = v.y * scale;
	res.z = v.z * scale;
	return res;
}