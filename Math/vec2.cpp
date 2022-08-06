#include "vec2.h"
#include <iostream>

const vec2 vec2::Zero = vec2(0., 0.);

const vec2 vec2::UnitX = vec2(1., 0.);
const vec2 vec2::UnitY = vec2(0., 1.);

const vec2 vec2::NegUnitX = vec2(-1., 0.);
const vec2 vec2::NegUnitY = vec2(0., -1.);

std::ostream& operator<<(std::ostream& stream, const vec2& vec)
{
	stream << " vec2 (x = " << vec.x << ", y = " << vec.y << ")\n";
	return stream;
}