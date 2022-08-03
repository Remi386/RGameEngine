#pragma once
#include <limits>
#include <cmath>

namespace Math {

	constexpr float Inf = std::numeric_limits<float>::infinity();
	constexpr float NegInf = -Inf;
	constexpr float PI = 3.1415927f;
	constexpr float float_error = 1.0f / 1e6f;

	inline float Pow(float value, float power)
	{
		return std::powf(value, power);
	}

	inline float Sqrt(float value)
	{
		return std::sqrtf(value);
	}

	inline float Cos(float angle)
	{
		return std::cosf(angle);
	}

	inline float Sin(float angle)
	{
		return std::sinf(angle);
	}

	inline float Tan(float angle)
	{
		return std::tanf(angle);
	}

	inline float Cot(float angle)
	{
		return 1.0f / Tan(angle);
	}

	inline float Atan(float angle)
	{
		return std::atanf(angle);
	}

	inline float Abs(float value)
	{
		return std::fabsf(value);
	}

	inline bool IsZero(float value)
	{
		return Abs(value) < float_error;
	}

	constexpr float ToRadians(float angle)
	{
		return angle * PI / 180.0f;
	}

	constexpr float ToDegrees(float angle)
	{
		return angle * 180.0f / PI;
	}

	inline bool IsFEqual(float first, float second)
	{
		return Abs(first - second) < float_error;
	}

	constexpr float Lerp(float start, float end, float timePoint)
	{
		return start + timePoint * (end - start);
	}
}