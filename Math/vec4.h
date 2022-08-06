#pragma once
#include "vec3.h"

class vec4 {
public:

	explicit constexpr vec4(float x_, float y_, float z_, float w_)
		:x(x_), y(y_), z(z_), w(w_)
	{}

	explicit constexpr vec4(const vec3& vec, float w_)
		: x(vec.x), y(vec.y), z(vec.z), w(w_)
	{}

	constexpr vec4& operator*=(float value)
	{
		x *= value; 
		y *= value; 
		z *= value;
		w *= value;
		return *this;
	}

	constexpr vec4& operator/=(float value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}

	constexpr vec4& operator*=(const vec4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	constexpr vec4& operator+=(const vec4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	constexpr vec4& operator-=(const vec4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	constexpr vec4& operator/=(const vec4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	friend constexpr vec4 operator*(float value, const vec4& vec)
	{
		vec4 tmp(vec);
		return tmp *= value;
	}

	friend constexpr vec4 operator*(const vec4& vec, float value)
	{
		return value * vec;
	}

	friend constexpr vec4 operator*(const vec4& vec1, const vec4& vec2)
	{
		vec4 tmp(vec1);
		return tmp *= vec2;
	}

	friend constexpr vec4 operator-(const vec4& vec1, const vec4& vec2)
	{
		vec4 tmp(vec1);
		return tmp -= vec2;
	}

	friend constexpr vec4 operator+(const vec4& vec1, const vec4& vec2)
	{
		vec4 tmp(vec1);
		return tmp += vec2;
	}

	friend constexpr vec4 operator/(const vec4& vec1, const vec4& vec2)
	{
		vec4 tmp(vec1);
		return tmp /= vec2;
	}

	const float* GetPointer() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	float x, y, z, w;
};