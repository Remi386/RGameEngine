#pragma once
#include <limits>
#include <cmath>

namespace Math {

	constexpr float Inf = std::numeric_limits<float>::infinity();
	constexpr float NegInf = -Inf;
	constexpr float PI = 3.1415927f;
	constexpr float float_error = 1.0 / 1e6;

	constexpr float Pow(float value, float power)
	{
		return std::powf(value, power);
	}

	constexpr float Sqrt(float value)
	{
		return std::sqrtf(value);
	}

	constexpr float Cos(float angle)
	{
		return std::cosf(angle);
	}

	constexpr float Sin(float angle)
	{
		return std::sinf(angle);
	}

	constexpr float Tan(float angle)
	{
		return std::tanf(angle);
	}

	constexpr float Cot(float angle)
	{
		return 1.0 / Tan(angle);
	}

	constexpr float Atan(float angle)
	{
		return std::atanf(angle);
	}

	constexpr float Abs(float value)
	{
		return std::fabsf(value);
	}

	constexpr bool IsZero(float value)
	{
		return std::fabs(value) <= float_error ? true : false;
	}

	constexpr float ToRadians(float angle)
	{
		return angle * PI / 180.0;
	}

	constexpr float ToDegrees(float angle)
	{
		return angle * 180.0 / PI;
	}

	constexpr float Lerp(float start, float end, float timePoint)
	{
		return start + timePoint * (end - start);
	}



}

