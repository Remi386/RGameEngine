#include "vec3.h"
#include "quaternion.h"

const vec3 vec3::Zero = vec3(0.0, 0.0, 0.0);

const vec3 vec3::UnitX = vec3(1.0, 0.0, 0.0);
const vec3 vec3::UnitY = vec3(0.0, 1.0, 0.0);
const vec3 vec3::UnitZ = vec3(0.0, 0.0, 1.0);

const vec3 vec3::NegUnitX = vec3(-1.0, 0.0, 0.0);
const vec3 vec3::NegUnitY = vec3(0.0, -1.0, 0.0);
const vec3 vec3::NegUnitZ = vec3(0.0, 0.0, -1.0);

vec3 vec3::Transform(const vec3& vec, const quat& rotation)
{
	vec3 qv(rotation.x, rotation.y, rotation.z);
	vec3 retVal = vec;
	retVal += 2.0f * vec3::Cross(qv, vec3::Cross(qv, vec) + rotation.w * vec);
	return retVal;
}

vec3 vec3::Transform(const vec3& vec, const mat4& mat, float w /* = 1.0*/)
{
	vec3 retVal;
	retVal.x = vec.x * mat[0][0] + vec.y * mat[1][0] +
		vec.z * mat[2][0] + w * mat[3][0];
	retVal.y = vec.x * mat[0][1] + vec.y * mat[1][1] +
		vec.z * mat[2][1] + w * mat[3][1];
	retVal.z = vec.x * mat[0][2] + vec.y * mat[1][2] +
		vec.z * mat[2][2] + w * mat[3][2];

	return retVal;
}