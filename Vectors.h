#pragma once

#define RAD2DEG(x) ((x) * 57.295754f)
#define DEG2RAD(x) ((x) * 0.0174533f)
#define CMP(x, y) \
	(fabsf(x - y) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))
class Vec2
{
public:
	float x, y;
	Vec2();
	Vec2(float x, float y);
	~Vec2();
	Vec2 operator+(Vec2 other);
	Vec2 operator-(Vec2 other);
	Vec2 operator*(float scalar);
	Vec2 operator/(float scalar);
	
	float dot(Vec2 other);
	Vec2 cross(Vec2 other);

	float magnitudeSq();
	float magnitude();
	Vec2 getNormal();
	void normalize();
};

class Vec3
{
public:
	float x, y, z;
	Vec3();
	Vec3(float x, float y, float z);
	~Vec3();
	Vec3 operator+(Vec3 other);
	Vec3 operator-(Vec3 other);
	Vec3 operator*(float scalar);
	Vec3 operator/(float scalar);

	float dot(Vec3 other);
	Vec3 cross(Vec3 other);

	float magnitudeSq();
	float magnitude();
	Vec3 getNormal();
	void normalize();

};

