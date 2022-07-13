#pragma once
#include "MathFunc.h"

class mat3 {
public:
	float m[3][3];

	mat3() 
	{
		*this = IdentityMatrix;
	}

	mat3(const float otherMat[3][3])
	{
		std::memcpy(m, otherMat, sizeof(float) * 9);
	}

	static mat3 CreateScale(float scaleX, float scaleY)
	{
		float mat[3][3] = {
			{scaleX, 0.0, 0.0},
			{0.0, scaleY, 0.0},
			{0.0, 0.0, 1.0}
		};
		return mat3(mat);
	}

	static mat3 CreateScale(float scale)
	{
		return CreateScale(scale, scale);
	}

	static mat3 CreateRotation(float theta)
	{
		float mat[3][3] =
		{
			{ Math::Cos(theta), Math::Sin(theta), 0.0f },
			{ -Math::Sin(theta), Math::Cos(theta), 0.0f },
			{ 0.0f, 0.0f, 1.0f },
		};
		return mat3(mat);
	}

	static mat3 CreateTranslation(float transX, float transY)
	{
		float mat[3][3] =
		{
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ transX, transY, 1.0f },
		};
		return mat3(mat);
	}

	float* GetPointer()
	{
		return reinterpret_cast<float*>(m);
	}

	static const mat3 IdentityMatrix;

};