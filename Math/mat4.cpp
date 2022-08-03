#include "mat4.h"
#include "vec3.h"
#include "quaternion.h"
#include "vec4.h"

mat4::mat4(const vec4& column1, const vec4& column2, const vec4& column3, const vec4& column4)
{
	std::memcpy(&m[0][0], column1.GetPointer(), 4 * sizeof(float));
	std::memcpy(&m[1][0], column2.GetPointer(), 4 * sizeof(float));
	std::memcpy(&m[2][0], column3.GetPointer(), 4 * sizeof(float));
	std::memcpy(&m[3][0], column4.GetPointer(), 4 * sizeof(float));
}

static const float IdentityMatrix4[4][4] =
{
	{1.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 1.0f}
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

mat4 mat4::CreateFromQuaternion(const quat& q)
{
	float mat[4][4];

	mat[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
	mat[0][1] = 2.0f * q.x  * q.y + 2.0f * q.w * q.z;
	mat[0][2] = 2.0f * q.x  * q.z - 2.0f * q.w * q.y;
	mat[0][3] = 0.0f;

	mat[1][0] = 2.0f * q.x  * q.y - 2.0f * q.w  * q.z;
	mat[1][1] = 1.0f - 2.0f * q.x * q.x  - 2.0f * q.z * q.z;
	mat[1][2] = 2.0f * q.y  * q.z + 2.0f * q.w  * q.x;
	mat[1][3] = 0.0f;

	mat[2][0] = 2.0f * q.x  * q.z + 2.0f * q.w  * q.y;
	mat[2][1] = 2.0f * q.y  * q.z - 2.0f * q.w  * q.x;
	mat[2][2] = 1.0f - 2.0f * q.x * q.x  - 2.0f * q.y * q.y;
	mat[2][3] = 0.0f;

	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;

	return mat4(mat);
}

mat4 mat4::CreateTranslation(const vec3& position)
{
	return CreateTranslation(position.x, position.y, position.z);
}

mat4 mat4::CreateLookAt(const vec3& eye, const vec3& target, const vec3& up)
{
	vec3 zaxis = vec3::Normalized(target - eye);
	vec3 xaxis = vec3::Normalized(vec3::Cross(up, zaxis));
	vec3 yaxis = vec3::Cross(zaxis, xaxis);
	vec3 trans;
	trans.x = -vec3::Dot(xaxis, eye);
	trans.y = -vec3::Dot(yaxis, eye);
	trans.z = -vec3::Dot(zaxis, eye);

	float temp[4][4] =
	{
		{ xaxis.x, yaxis.x, zaxis.x, 0.0f },
		{ xaxis.y, yaxis.y, zaxis.y, 0.0f },
		{ xaxis.z, yaxis.z, zaxis.z, 0.0f },
		{ trans.x, trans.y, trans.z, 1.0f }
	};
	return mat4(temp);
}

float mat4::Determinant() const
{
	float Sub0 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
	float Sub1 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
	float Sub2 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
	float Sub3 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
	float Sub4 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
	float Sub5 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

	vec4 Det(
		 (m[1][1] * Sub0 - m[1][2] * Sub1 + m[1][3] * Sub2),
		-(m[1][0] * Sub0 - m[1][2] * Sub3 + m[1][3] * Sub4),
		 (m[1][0] * Sub1 - m[1][1] * Sub3 + m[1][3] * Sub5),
		-(m[1][0] * Sub2 - m[1][1] * Sub4 + m[1][2] * Sub5)
	);

	return m[0][0] * Det.x + m[0][1] * Det.y + m[0][2] * Det.z + m[0][3] * Det.w;
}

void mat4::Inverse()
{
	float Coof00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
	float Coof02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
	float Coof03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
		   
	float Coof04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
	float Coof06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
	float Coof07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
		   
	float Coof08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
	float Coof10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
	float Coof11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
		   
	float Coof12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
	float Coof14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
	float Coof15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

	float Coof16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
	float Coof18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
	float Coof19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

	float Coof20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
	float Coof22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
	float Coof23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

	vec4 Fac0(Coof00, Coof00, Coof02, Coof03);
	vec4 Fac1(Coof04, Coof04, Coof06, Coof07);
	vec4 Fac2(Coof08, Coof08, Coof10, Coof11);
	vec4 Fac3(Coof12, Coof12, Coof14, Coof15);
	vec4 Fac4(Coof16, Coof16, Coof18, Coof19);
	vec4 Fac5(Coof20, Coof20, Coof22, Coof23);

	vec4 Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
	vec4 Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
	vec4 Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
	vec4 Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

	vec4 Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
	vec4 Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
	vec4 Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
	vec4 Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

	Inv0.y *= -1;
	Inv0.w *= -1;

	Inv1.x *= -1;
	Inv1.z *= -1;

	Inv2.y *= -1;
	Inv2.z *= -1;

	Inv3.x *= -1;
	Inv3.z *= -1;

	mat4 Invers(Inv0, Inv1, Inv2, Inv3);

	vec4 Row0(Invers[0][0], Invers[1][0], Invers[2][0], Invers[3][0]);

	vec4 DotVec(vec4(m[0][0], m[0][1], m[0][2], m[0][3]) * Row0);

	float DotSc = (DotVec.x + DotVec.y) + (DotVec.z + DotVec.w);

	float OneOverDet = 1.0f / DotSc;

	(*this) = Invers * OneOverDet;
}

mat4 mat4::Inversed(const mat4& m)
{
	mat4 tmp = m;
	tmp.Inverse();
	return tmp;
}