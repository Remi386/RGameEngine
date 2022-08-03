#pragma once
#include "MathFunc.h"

class quat;
class vec3;
class vec4;

class mat4 {
public:
	float m[4][4];

	mat4()
	{
		*this = IdentityMatrix;
	}

	mat4(const float otherMat[4][4])
	{
		std::memcpy(m, otherMat, sizeof(float) * 16);
	}

	mat4(const vec4& column1, const vec4& column2, const vec4& column3, const vec4& column4);

	const float* GetPointer() const
	{
		return reinterpret_cast<const float*>(m);
	}

	float* operator[](size_t RowIndex)
	{
		return m[RowIndex];
	}

	const float* operator[](size_t RowIndex) const
	{
		return m[RowIndex];
	}

	mat4& operator*=(float value)
	{
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				m[i][j] *= value;
			}
		}
		return *this;
	}

	friend mat4 operator*(const mat4& mat, float value)
	{
		mat4 tmp = mat;
		tmp *= value;

		return tmp;
	}

	friend mat4 operator*(float value, const mat4& mat)
	{
		return mat * value;
	}

	friend mat4 operator*(const mat4& lhs, const mat4& rhs);

	friend mat4 operator*(const mat4& lhs, const mat4& rhs);

	mat4& operator*=(const mat4& other)
	{
		*this = *this * other;
		return *this;
	}

	static mat4 CreateScale(float scaleX, float scaleY, float scaleZ)
	{
		float mat[4][4] =
		{
			{ scaleX, 0.0f,   0.0f,   0.0f },
			{ 0.0f,   scaleY, 0.0f,   0.0f },
			{ 0.0f,   0.0f,   scaleZ, 0.0f },
			{ 0.0f,   0.0f,   0.0f,   1.0f }
		};
		return mat4(mat);
	}

	static mat4 CreateScale(float scale)
	{
		return CreateScale(scale, scale, scale);
	}

	static mat4 CreateTranslation(float transX, float transY, float transZ)
	{
		float mat[4][4] =
		{
			{ 1.0f,   0.0f,   0.0f,   0.0f },
			{ 0.0f,   1.0f,   0.0f,   0.0f },
			{ 0.0f,   0.0f,   1.0f,   0.0f },
			{ transX, transY, transZ, 1.0f }
		};
		return mat4(mat);
	}

	static mat4 CreateTranslation(const vec3& position);

	static mat4 CreateRotationX(float angle)
	{
		float mat[4][4] =
		{
			{ 1.0f, 0.0f,              0.0f ,            0.0f },
			{ 0.0f, Math::Cos(angle),  Math::Sin(angle), 0.0f },
			{ 0.0f, -Math::Sin(angle), Math::Cos(angle), 0.0f },
			{ 0.0f, 0.0f,              0.0f,             1.0f },
		};
		return mat4(mat);
	}

	static mat4 CreateRotationY(float angle)
	{
		float mat[4][4] =
		{
			{ Math::Cos(angle), 0.0f, -Math::Sin(angle), 0.0f },
			{ 0.0f,             1.0f, 0.0f,              0.0f },
			{ Math::Sin(angle), 0.0f, Math::Cos(angle),  0.0f },
			{ 0.0f,             0.0f, 0.0f,              1.0f },
		};
		return mat4(mat);
	}

	static mat4 CreateRotationZ(float angle)
	{
		float mat[4][4] =
		{
			{ Math::Cos(angle),  Math::Sin(angle), 0.0f, 0.0f },
			{ -Math::Sin(angle), Math::Cos(angle), 0.0f, 0.0f },
			{ 0.0f,              0.0f,             1.0f, 0.0f },
			{ 0.0f,              0.0f,             0.0f, 1.0f },
		};
		return mat4(mat);
	}

	static mat4 CreateFromQuaternion(const quat& q);

	static mat4 CreateOrthogonal(float width, float height, float near, float far)
	{
		float mat[4][4] =
		{
			{ 2.0f/width, 0.0f,        0.0f,              0.0f },
			{ 0.0f,       2.0f/height, 0.0f,              0.0f },
			{ 0.0f,       0.0f,        1.0f/(far - near), 0.0f },
			{ 0.0f,       0.0f,        near/(near - far), 1.0f }
		};
		return mat4(mat);
	}

	static mat4 CreatePerspective(float FOV, float width, float height, float near, float far)
	{
		float yScale = Math::Cot(FOV / 2.0f);
		float xScale = yScale * height / width;
		float mat[4][4] =
		{
			{ xScale, 0.0f,   0.0f,                                  0.0f },
			{ 0.0f,   yScale, 0.0f,                                  0.0f },
			{ 0.0f,   0.0f,   (far + near) / (far - near),             1.0f },
			{ 0.0f,   0.0f,   -(2 * near * far) / (far - near),        0.0f }
		};
		return mat4(mat);
	}

	static mat4 CreateLookAt(const vec3& eye, const vec3& target, const vec3& up);

	float Determinant() const;

	void Inverse();

	static mat4 Inversed(const mat4& mat);

	static const mat4 IdentityMatrix;
};