#include "mat4.h"

mat4 operator*(const mat4& lhs, const mat4& rhs)
{
	mat4 resultMatrix;

	resultMatrix.m[0][0] =
		lhs.m[0][0] * rhs.m[0][0] +
		lhs.m[0][1] * rhs.m[1][0] +
		lhs.m[0][2] * rhs.m[2][0] +
		lhs.m[0][3] * rhs.m[3][0];

	resultMatrix.m[0][1] =
		lhs.m[0][0] * rhs.m[0][1] +
		lhs.m[0][1] * rhs.m[1][1] +
		lhs.m[0][2] * rhs.m[2][1] +
		lhs.m[0][3] * rhs.m[3][1];

	resultMatrix.m[0][2] =
		lhs.m[0][0] * rhs.m[0][2] +
		lhs.m[0][1] * rhs.m[1][2] +
		lhs.m[0][2] * rhs.m[2][2] +
		lhs.m[0][3] * rhs.m[3][2];

	resultMatrix.m[0][3] =
		lhs.m[0][0] * rhs.m[0][3] +
		lhs.m[0][1] * rhs.m[1][3] +
		lhs.m[0][2] * rhs.m[2][3] +
		lhs.m[0][3] * rhs.m[3][3];

	resultMatrix.m[1][0] =
		lhs.m[1][0] * rhs.m[0][0] +
		lhs.m[1][1] * rhs.m[1][0] +
		lhs.m[1][2] * rhs.m[2][0] +
		lhs.m[1][3] * rhs.m[3][0];

	resultMatrix.m[1][1] =
		lhs.m[1][0] * rhs.m[0][1] +
		lhs.m[1][1] * rhs.m[1][1] +
		lhs.m[1][2] * rhs.m[2][1] +
		lhs.m[1][3] * rhs.m[3][1];

	resultMatrix.m[1][2] =
		lhs.m[1][0] * rhs.m[0][2] +
		lhs.m[1][1] * rhs.m[1][2] +
		lhs.m[1][2] * rhs.m[2][2] +
		lhs.m[1][3] * rhs.m[3][2];

	resultMatrix.m[1][3] =
		lhs.m[1][0] * rhs.m[0][3] +
		lhs.m[1][1] * rhs.m[1][3] +
		lhs.m[1][2] * rhs.m[2][3] +
		lhs.m[1][3] * rhs.m[3][3];

	resultMatrix.m[2][0] =
		lhs.m[2][0] * rhs.m[0][0] +
		lhs.m[2][1] * rhs.m[1][0] +
		lhs.m[2][2] * rhs.m[2][0] +
		lhs.m[2][3] * rhs.m[3][0];

	resultMatrix.m[2][1] =
		lhs.m[2][0] * rhs.m[0][1] +
		lhs.m[2][1] * rhs.m[1][1] +
		lhs.m[2][2] * rhs.m[2][1] +
		lhs.m[2][3] * rhs.m[3][1];

	resultMatrix.m[2][2] =
		lhs.m[2][0] * rhs.m[0][2] +
		lhs.m[2][1] * rhs.m[1][2] +
		lhs.m[2][2] * rhs.m[2][2] +
		lhs.m[2][3] * rhs.m[3][2];

	resultMatrix.m[2][3] =
		lhs.m[2][0] * rhs.m[0][3] +
		lhs.m[2][1] * rhs.m[1][3] +
		lhs.m[2][2] * rhs.m[2][3] +
		lhs.m[2][3] * rhs.m[3][3];

	resultMatrix.m[3][0] =
		lhs.m[3][0] * rhs.m[0][0] +
		lhs.m[3][1] * rhs.m[1][0] +
		lhs.m[3][2] * rhs.m[2][0] +
		lhs.m[3][3] * rhs.m[3][0];

	resultMatrix.m[3][1] =
		lhs.m[3][0] * rhs.m[0][1] +
		lhs.m[3][1] * rhs.m[1][1] +
		lhs.m[3][2] * rhs.m[2][1] +
		lhs.m[3][3] * rhs.m[3][1];

	resultMatrix.m[3][2] =
		lhs.m[3][0] * rhs.m[0][2] +
		lhs.m[3][1] * rhs.m[1][2] +
		lhs.m[3][2] * rhs.m[2][2] +
		lhs.m[3][3] * rhs.m[3][2];

	resultMatrix.m[3][3] =
		lhs.m[3][0] * rhs.m[0][3] +
		lhs.m[3][1] * rhs.m[1][3] +
		lhs.m[3][2] * rhs.m[2][3] +
		lhs.m[3][3] * rhs.m[3][3];

	return resultMatrix;
}

