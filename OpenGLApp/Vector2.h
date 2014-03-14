#pragma once

#include <cmath>

#include "stdincludes.h"

struct Vector2
{
	Vector2() {}
	Vector2(float x, float y) : x(x), y(y) {}

	operator const float *() const { return &x; }
	operator float *() { return &x; }

	void Set(float x_, float y_) { x = x_; y = y_; }

	Vector2 operator -() { return Vector2(-x, -y); }
	
	void operator += (const Vector2& v)
	{
		x += v.x; y += v.y;
	}
	
	void operator -= (const Vector2& v)
	{
		x -= v.x; y -= v.y;
	}

	void operator *= (float a)
	{
		x *= a; y *= a;
	}

	float Length() const
	{
		return sqrtf(x * x + y * y);
	}

	float SquaredLength() const 
	{
		return x*x+y*y;
	}

	float x, y;
};


inline float Dot(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}

inline float Cross(const Vector2& a, const Vector2& b)
{
	return a.x * b.y - a.y * b.x;
}

inline Vector2 Cross(const Vector2& a, float s)
{
	return Vector2(s * a.y, -s * a.x);
}

inline Vector2 Cross(float s, const Vector2& a)
{
	return Vector2(-s * a.y, s * a.x);
}

inline Vector2 operator + (const Vector2& a, const Vector2& b)
{
	return Vector2(a.x + b.x, a.y + b.y);
}

inline Vector2 operator - (const Vector2& a, const Vector2& b)
{
	return Vector2(a.x - b.x, a.y - b.y);
}

inline Vector2 operator * (float s, const Vector2& v)
{
	return Vector2(s * v.x, s * v.y);
}
