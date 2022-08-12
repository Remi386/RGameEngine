#pragma once
#include "vec3.h"
#include "mat4.h"
#include <iosfwd>

class quat {
public:

	float x;
	float y;
	float z;
	float w;

	quat()
		:x(0.0f), y(0.0f), z(0.0f), w(1.0)
	{}

	explicit constexpr quat(float x_, float y_, float z_, float w_)
	{
		x = x_;
		y = y_;
		z = z_;
		w = w_;
	}
	
	explicit quat(const vec3& axis, float angle)
	{
		float sinus = Math::Sin(angle / 2);
		x = axis.x * sinus;
		y = axis.y * sinus;
		z = axis.z * sinus;
		w = Math::Cos(angle / 2);
	}

	void Conjugate()
	{
		x *= -1.0f;
		y *= -1.0f;
		z *= -1.0f;
	}

	static quat Conjugated(const quat& qua)
	{
		quat tmp = qua;
		tmp.Conjugate();
		return tmp;
	}

	float LengthSquared() const
	{
		return (x * x + y * y + z * z + w * w);
	}

	float Length() const
	{
		return Math::Sqrt(LengthSquared());
	}

	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	quat& operator*=(const quat& other)
	{
		vec3 qv(x, y, z);
		vec3 pv(other.x, other.y, other.z);
		vec3 newVec = other.w * qv + w * pv + vec3::Cross(pv, qv);

		x = newVec.x;
		y = newVec.y;
		z = newVec.z;

		w = other.w * w - vec3::Dot(pv, qv);
		return *this;
	}

	static quat Concatenate(const quat& q, const quat& p)
	{
		quat result = q;
		result *= p;
		return result;
	}

	static quat Normalized(const quat& qua)
	{
		quat tmp = qua;
		tmp.Normalize();
		return tmp;
	}

	static quat CreateFromMatrix(const mat4& mat);
	
	friend std::ostream& operator<<(std::ostream& stream, const quat& vec);

};