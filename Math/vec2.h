#pragma once
#include "MathFunc.h"

class vec2 {
public:

	explicit constexpr vec2(float x_ = 0.0, float y_ = 0.0)
	{
		x = x_; y = y_;
	}

	constexpr float LengthSqured()
	{
		return x*x + y*y;
	}

	inline float Length()
	{
		return Math::Sqrt(LengthSqured());
	}

	inline void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	static vec2 Normalized(const vec2& vec)
	{
		vec2 tmp = vec;
		tmp.Normalize();
		return tmp;
	}

	static float Dot(const vec2& lhs, const vec2& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	static vec2 Lerp(const vec2& start, const vec2& end, float time)
	{
		return vec2(start + time * (end - start));
	}
	
	static vec2 Reflect(const vec2& v, const vec2& n)
	{
		return v - 2.0f * Dot(v, n) * n;
	}

	const float* GetPointer() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	vec2& operator=(const vec2& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	vec2& operator-=(const vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	vec2& operator+=(const vec2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	vec2& operator/=(const vec2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	vec2& operator*=(const vec2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	friend vec2 operator*(const vec2& vec, float scale)
	{
		return vec2(vec.x * scale, vec.x * scale);
	}

	friend vec2 operator*(float scale, const vec2& vec)
	{
		return vec2(vec.x * scale, vec.x * scale);
	}

	friend vec2 operator+(const vec2& lhs, const vec2& rhs)
	{
		return vec2(lhs.x + rhs.x, lhs.x + rhs.x);
	}

	friend vec2 operator-(const vec2& lhs, const vec2& rhs)
	{
		return vec2(lhs.x - rhs.x, lhs.x - rhs.x);
	}

	friend vec2 operator*(const vec2& lhs, const vec2& rhs)
	{
		return vec2(lhs.x * rhs.x, lhs.x * rhs.x);
	}

	friend vec2 operator/(const vec2& lhs, const vec2& rhs)
	{
		return vec2(lhs.x / rhs.x, lhs.x / rhs.x);
	}

	static const vec2 Zero;

	static const vec2 UnitX;
	static const vec2 UnitY;

	static const vec2 NegUnitX;
	static const vec2 NegUnitY;

	float x;
	float y;
};

//using vec2f = vec2<float>;
//using vec2i = vec2<int>;