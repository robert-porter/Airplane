#pragma once

#include "stdincludes.h"

class Color4f
{
public:
	Color4f(void);
	Color4f(float red, float green, float blue, float alpha) : r(red), g(green), b(blue), a(alpha) { }

	float r, g, b, a;
};
