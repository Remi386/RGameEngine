#include "quaternion.h"
#include <iostream>

quat quat::CreateFromMatrix(const mat4& mat)
{
	float q[4] = { 0, 0, 0, 0 };
	float trace = mat[0][0] + mat[1][1] + mat[2][2];

	if (trace > 0.0f) {
		float s = sqrt(trace + 1.0f);
		q[3] = s * 0.5f;
		float t = 0.5f / s;
		q[0] = (mat[2][1] - mat[1][2]) * t;
		q[1] = (mat[0][2] - mat[2][0]) * t;
		q[2] = (mat[1][0] - mat[0][1]) * t;
	}
	else {
		int i = 0;

		if (mat[1][1] > mat[0][0])
			i = 1;

		if (mat[2][2] > mat[i][i])
			i = 2;

		const int NEXT[3] = { 1, 2, 0 };

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

std::ostream& operator<<(std::ostream& stream, const quat& qua)
{
	stream << " quat (x = " << qua.x << ", y = " << qua.y 
		   << ", z = " << qua.z << ", w = " << qua.w << ")\n";

	return stream;
}