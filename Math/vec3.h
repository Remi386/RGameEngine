#pragma once
#include "MathFunc.h"

class vec3 {
public:

	float x;
	float y;
	float z;

	constexpr vec3(float x_ = 0.0, float y_ = 0.0, float z_ = 0.0)
	{
		x = x_;
		y = y_;
		z = z_;
	}

	constexpr float LengthSqured()
	{
		return x*x + y*y + z*z;
	}

	constexpr float Length()
	{
		return Math::Sqrt(LengthSqured());
	}

	constexpr void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
	}

	static float Dot(const vec3& lhs, const vec3& rhs)
	{
		return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
	}

	static vec3 Cross(const vec3& lhs, const vec3& rhs)
	{
		vec3 tmp;
		tmp.x = lhs.y * rhs.z - lhs.z * rhs.y;
		tmp.y = lhs.z * rhs.x - lhs.x * rhs.z;
		tmp.z = lhs.x * rhs.y - lhs.y * rhs.x;
		return tmp;
	}

	vec3& operator-=(const vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3& operator+=(const vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3& operator*=(const vec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	vec3& operator/=(const vec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	friend vec3 operator*(const vec3& vec, float scale)
	{
		return vec3(vec.x * scale, vec.y * scale, vec.z * scale);
	}

	friend vec3 operator*(float scale, const vec3& vec)
	{
		return vec3(vec.x * scale, vec.y * scale, vec.z * scale);
	}

	friend vec3 operator-(const vec3& lhs, const vec3& rhs)
	{
		return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	friend vec3 operator+(const vec3& lhs, const vec3& rhs)
	{
		return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	friend vec3 operator*(const vec3& lhs, const vec3& rhs)
	{
		return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	friend vec3 operator/(const vec3& lhs, const vec3& rhs)
	{
		return vec3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}

	static const vec3 Zero;

	static const vec3 UnitX;
	static const vec3 UnitY;
	static const vec3 UnitZ;
	
	static const vec3 NegUnitX;
	static const vec3 NegUnitY;
	static const vec3 NegUnitZ;

};