#pragma once

#include "Vector2.h"
#include "MathUtils.h"


class Path
{
public:
	Path(Vector2 *p, int n, bool loop);
	~Path(void);

	Vector2 GetPosition();
	float   GetRotation();
	void    Advance(float distance);

private:
	int GetNextIndex(int i) { i++; if(loop) i = i % (numPoints); return i; }
	float GetAngle(int i) { 	
		Vector2 v = points[GetNextIndex(index)] - points[index];
	    return  atan2f(v.y, v.x) + PI * 0.5f;
	}
	void Draw();

	Vector2 *points;
	float   *lengths;
	int     numPoints;
	float   totalLength;

	float   length;
	float   segmentLength;
	int     index;

	Vector2 position;
	float   rotation;

	bool    loop;
};
