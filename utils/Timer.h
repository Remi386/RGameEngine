#pragma once
#include <cstdint>

inline constexpr int MaxFrameKeep = 30;

class Timer {
public:
	Timer();

	void SetScale(float scale = 1.0) { time_scale = scale; }

	bool WaitForFrameEnd();

	float GetFrameDifference();

	void UpdateTimer();

	float GetAverage();

	uint64_t GetTimePoint();

private:
	uint64_t frameTimeBuffer[MaxFrameKeep];
	float time_scale = 1.0f;
};