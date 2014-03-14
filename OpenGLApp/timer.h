#pragma once


#include "stdincludes.h"

class FrameTimer
{
 public:
	static void		Start();
	static void		Frame(); 
	static double	DeltaTime();	
	static double	Time();	
private:
	static double	time0;
	static double	time;
	static double	deltaTime;
};

