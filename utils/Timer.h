#pragma once
#include <cstdint>

inline constexpr int MaxFrameKeep = 30;

class Timer {
public:
	enum class FrameRate : int {
		Unlimited,
		FPS5 = 5,
		FPS10 = 10,
		FPS15 = 15,
		FPS24 = 24,
		FPS30 = 30,
		FPS50 = 50,
		FPS60 = 60
	};

	Timer(FrameRate frameRate);

	void SetFrameRate(FrameRate rate) { fRate = rate; }

	void SetScale(float scale = 1.0) { time_scale = scale; }

	bool IsFrameEnd();

	float GetFrameDifference();

	void UpdateTimer();

	float GetFPS();

	uint64_t GetTimePoint();

private:
	FrameRate fRate = FrameRate::FPS30;
	uint64_t frameTimeBuffer[MaxFrameKeep];
	float time_scale = 1.0f;
};