#pragma once
#include "MathFunc.h"
#include <iosfwd>

class quat;
class mat4;

class vec3 {
public:

	float x;
	float y;
	float z;

	explicit constexpr vec3(float x_ = 0.0, float y_ = 0.0, float z_ = 0.0)
		:x(x_), y(y_), z(z_)
	{}

	const float* GetPointer() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	constexpr float LengthSqured() const
	{
		return x*x + y*y + z*z;
	}

	float Length() const
	{
		return Math::Sqrt(LengthSqured());
	}

	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
	}

	static vec3 Reflect(const vec3& v, const vec3& n)
	{
		return v - 2.0f * Dot(v, n) * n;
	}

	static vec3 Normalized(const vec3& vec)
	{
		vec3 tmp = vec;
		tmp.Normalize();
		return tmp;
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

	static vec3 Transform(const vec3& vec, const quat& rotation);

	static vec3 Transform(const vec3& vec, const mat4& rotation, float w = 1.0);

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

	friend std::ostream& operator<<(std::ostream& stream, const vec3& vec);

	static const vec3 Zero;

	static const vec3 UnitX;
	static const vec3 UnitY;
	static const vec3 UnitZ;
	
	static const vec3 NegUnitX;
	static const vec3 NegUnitY;
	static const vec3 NegUnitZ;

};