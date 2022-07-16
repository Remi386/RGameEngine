#include "mat4.h"
#include "quaterion.h"

static const float IdentityMatrix4[4][4] =
{
	{1.0, 0.0, 0.0, 0.0},
	{0.0, 1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 1.0}
};

const mat4 mat4::IdentityMatrix = mat4(IdentityMatrix4);

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

mat4 CreateFromQuaterion(const quat& q)
{
	float mat[4][4];

	mat[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
	mat[0][1] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
	mat[0][2] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
	mat[0][3] = 0.0f;

	mat[1][0] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
	mat[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
	mat[1][2] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;
	mat[1][3] = 0.0f;

	mat[2][0] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
	mat[2][1] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
	mat[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
	mat[2][3] = 0.0f;

	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;

	return mat4(mat);
}

