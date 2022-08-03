#pragma once
#include "vec3.h"
#include "mat4.h"

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
	
	explicit inline quat(const vec3& axis, float angle)
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

	static quat CreateFromMatrix(const mat4& mat)
	{
		float q[4] = {0, 0, 0, 0};
		float trace = mat[0][0] + mat[1][1] + mat[2][2];
		// проверяем диагональ
		if (trace > 0.0f) {
			float s = sqrt(trace + 1.0f);
			q[3] = s * 0.5f;
			float t = 0.5f / s;
			q[0] = (mat[2][1] - mat[1][2]) * t;
			q[1] = (mat[0][2] - mat[2][0]) * t;
			q[2] = (mat[1][0] - mat[0][1]) * t;
		}
		else {
			// диагональ отрицательна
			int i = 0;
			
			if (mat[1][1] > mat[0][0]) 
				i = 1;

			if (mat[2][2] > mat[i][i]) 
				i = 2;

			static const int NEXT[3] = { 1, 2, 0 };
			int j = NEXT[i];
			int k = NEXT[j];
			float s = sqrt((mat[i][j] - (mat[j][j] + mat[k][k])) + 1.0f);
			q[i] = s * 0.5f;
			float t;

			if (s != 0.0) 
				t = 0.5f / s;
			else 
				t = s;

			q[3] = (mat[k][j] - mat[j][k]) * t;
			q[j] = (mat[j][i] + mat[i][j]) * t;
			q[k] = (mat[k][i] + mat[i][k]) * t;
		}
		return quat(q[0], q[1], q[2], q[3]);
	}
	
};