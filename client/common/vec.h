#pragma once

typedef union Vec3 {
	 float m[3];
	 struct {
	 	float x, y, z;
	 };
} Vec3;

typedef union Vec2 {
	 float m[2];
	 struct {
	 	float x, y;
	 };
} Vec2;