#include "mat3.h"

const float IdentityMat3[3][3] ={ 
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0 };

const mat3 mat3::IdentityMatrix = mat3(IdentityMat3);