#include "Vectors.h"
#include <iostream>

Vec2::Vec2()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vec2::Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vec2::~Vec2()
{
}

Vec2 Vec2::operator+(Vec2 other)
{
	return Vec2(this->x + x, this->y + y);
}

Vec2 Vec2::operator-(Vec2 other)
{
	return Vec2(this->x - x, this->y - y);
}

Vec2 Vec2::operator*(float scalar)
{
	return Vec2(this->x * scalar, this->y * scalar);
}

Vec2 Vec2::operator/(float scalar)
{
	if (scalar == 0)
	{
		throw std::runtime_error("Vec2::ERROR - Cannot divide by zero.\n");
	}
	return Vec2(this->x / scalar, this->y / scalar);
}

Vec2 Vec2::cross(Vec2 other)
{
	return Vec2(this->x * other.y, this->y * other.x);
}

float Vec2::magnitudeSq()
{
	return this->x * this->x + this->y * this->y;
}

float Vec2::magnitude()
{
	return sqrt(this->x * this->x + this->y * this->y);
}

Vec2 Vec2::getNormal()
{
	return *this / magnitude();
}

void Vec2::normalize()
{
	float mag = magnitude();
	this->x / mag;
	this->y / mag;
}

float Vec2::dot(Vec2 other)
{
	return this->x * x + this->y * y;
}

Vec3::Vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vec3::Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3::~Vec3()
{
}

Vec3 Vec3::operator+(Vec3 other)
{
	return Vec3(this->x + x, this->y + y, this->z + z);
}

Vec3 Vec3::operator-(Vec3 other)
{
	return Vec3(this->x - x, this->y - y, this->z - z);
}

Vec3 Vec3::operator*(float scalar)
{
	return Vec3(this->x * scalar, this->y * scalar, this->z * scalar);
}

Vec3 Vec3::operator/(float scalar)
{
	if (scalar == 0) {
		throw std::runtime_error("Vec3::ERRRO - Cannot divide by zero.\n");
	}
	return Vec3(this->x / scalar, this->y / scalar, this->z / scalar);
}

Vec3 Vec3::cross(Vec3 other)
{
	float i = this->y * other.z - this->z * other.y;
	float j = this->z * other.x - this->x * other.z;
	float k = this->x * other.y - this->y * other.x;
	return Vec3(i, j, k);
}

float Vec3::magnitudeSq()
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

float Vec3::magnitude()
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vec3 Vec3::getNormal()
{
	return *this / magnitude();
}

void Vec3::normalize()
{
	float mag = magnitude();
	this->x / mag;
	this->y / mag;
	this->z / mag;
}

float Vec3::dot(Vec3 other)
{
	return this->x * x + this->y * y + this->z * z;
}
