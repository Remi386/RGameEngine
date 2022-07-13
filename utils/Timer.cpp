#include "Timer.h"
#include <chrono>
using mClock = std::chrono::steady_clock;

constexpr float nanInSec = 0.000'001;

Timer::Timer()
{
	std::memset(frameTimeBuffer, 0, MaxFrameKeep);
}

float Timer::GetFrameDifference()
{
	return float(frameTimeBuffer[MaxFrameKeep - 1] - frameTimeBuffer[MaxFrameKeep - 2]);
}

void Timer::UpdateTimer()
{
	for (int i = 0; i < MaxFrameKeep - 1; i++) {
		frameTimeBuffer[i] = frameTimeBuffer[i + 1];
	}
	frameTimeBuffer[MaxFrameKeep - 1] = GetTimePoint();
}

bool Timer::WaitForFrameEnd()
{
	return true;
}

float Timer::GetAverage()
{
	uint64_t time_diff = frameTimeBuffer[MaxFrameKeep - 1] - frameTimeBuffer[0];
	float(time_diff) * nanInSec;
}

uint64_t Timer::GetTimePoint()
{
	return mClock::now().time_since_epoch().count();
}