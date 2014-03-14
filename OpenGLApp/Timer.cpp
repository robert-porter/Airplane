#include "Timer.h"

double FrameTimer::time0 = 0.0;
double FrameTimer::time = 0.0;
double FrameTimer::deltaTime = 0.0;


void FrameTimer::Start()
{
	time0 = GetTickCount() / 1000.0;
	time = time0;
	deltaTime = 0.0f;
}

void FrameTimer::Frame()
{
	double oldTime = time;
	time = GetTickCount() / 1000.0;
	deltaTime = time - oldTime;
}

double FrameTimer::DeltaTime()
{
	return deltaTime;
}

double FrameTimer::Time() 
{
	return time - time0;
}