#include "Timer.h"
#include <chrono>
using mClock = std::chrono::steady_clock;

constexpr float nanInSec = 1.0E-9f;

Timer::Timer(FrameRate frameRate)
	:fRate(frameRate)
{
	uint64_t timePoint = GetTimePoint();
	std::fill(&frameTimeBuffer[0], &frameTimeBuffer[MaxFrameKeep], timePoint);
}

float Timer::GetFrameDifference()
{
	return time_scale * nanInSec * 
		   float(frameTimeBuffer[MaxFrameKeep - 1] - frameTimeBuffer[MaxFrameKeep - 2]);
}

void Timer::UpdateTimer()
{
	for (int i = 0; i < MaxFrameKeep - 1; i++) {
		frameTimeBuffer[i] = frameTimeBuffer[i + 1];
	}
	frameTimeBuffer[MaxFrameKeep - 1] = GetTimePoint();
}

bool Timer::IsFrameEnd()
{
	return (float(GetTimePoint() - frameTimeBuffer[MaxFrameKeep - 1]) * nanInSec)
			> (1.0f / float(fRate));
}

//float Timer::GetAverage()
//{
//	uint64_t time_diff = frameTimeBuffer[MaxFrameKeep - 1] - frameTimeBuffer[0];
//	return float(time_diff) * nanInSec;
//}

uint64_t Timer::GetTimePoint()
{
	return mClock::now().time_since_epoch().count();
}
