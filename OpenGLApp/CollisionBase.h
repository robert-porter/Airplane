#pragma once

#include "Vector2.h"
#include "MathUtils.h"




// finds the squared distance from the point P to the Segment P0P1
inline float SquaredDistancePointSegment(const Vector2 &P, const Vector2 &P0, const Vector2 &P1)
{

	Vector2 d = P1-P0;
	Vector2 Prel = P-P0;
	float t = Dot(d, Prel);

	if(t < 0) // closest to P0
		return Prel.SquaredLength();

	float ddotd = Dot(d,d);
	
	if(t > ddotd) // closest to P1
	{
		return (P - P1).SquaredLength();
	}

   	return Dot(Prel, Prel) - t*t / ddotd;  // closest to a point on the interior of the segment
}

//Test the circles |X-P0|<=r0 and |X-P1|<=r1 for intersection
inline bool IntersectCircleCircle(const Vector2& P0, float r0, const Vector2& P1, float r1)
{

	float r = r0 + r1;
	return (P1-P0).SquaredLength() <= r*r;
}

inline bool IntersectCircleCapsule(const Vector2 &P0, float r0, const Vector2 &A, const Vector2 &B, float r1)
{
	float r = r0 + r1;
	return SquaredDistancePointSegment(P0, A, B) <= r*r;
}