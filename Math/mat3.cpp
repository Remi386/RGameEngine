#include "mat3.h"
#include <iostream>
#include <iomanip>

const float IdentityMat3[3][3] ={ 
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0 };

const mat3 mat3::IdentityMatrix = mat3(IdentityMat3);

std::ostream& operator<<(std::ostream& stream, const mat3& mat)
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			std::cout << std::setw(8) << mat[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
	return stream;
}