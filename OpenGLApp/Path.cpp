#include "Path.h"
#include <cfloat>
#include "MathUtils.h"
#include "Renderer.h"

Path::Path(Vector2 *p, int n, bool loop)
{
	points = 0;
	lengths = 0;
	points = new Vector2[n];
	lengths = new float[n];
	numPoints = n;

	this->loop = loop;

	for(int i = 0; i < n; i++)
		points[i] = p[i];
	for(int i = 1; i < n; i++)
		lengths[i-1] = (p[i] - p[i - 1]).Length();
	if(loop)
		lengths[n-1] = (p[0] - p[n - 1]).Length();
	else             // 
		lengths[n-1] = FLT_MAX;

	totalLength = 0.0f;
	for(int i = 0; i < numPoints - 1; i++)
	{
		totalLength += lengths[i];
	}

	length = 0.0f;
	segmentLength = 0.0f;
	index = 0;
}

Path::~Path(void)
{
	if(lengths)
		delete[] lengths;
	if(points)
		delete[] points;

}

Vector2 Path::GetPosition()
{
	return position;
}

float Path::GetRotation()
{
	return rotation;
}


void Path::Advance(float distance)
{
	length += distance;
	segmentLength += distance;


	if(loop || length < totalLength)
	{
		while(segmentLength > lengths[index])
		{
			segmentLength -= lengths[index];
			index = GetNextIndex(index);
		}
	}

	float t = segmentLength / lengths[index];
    position  = points[index] + t * (points[GetNextIndex(index)] - points[index]);
	rotation = t * GetAngle(index) + (1.0f - t) * GetAngle(GetNextIndex(index));

//	Draw();
}

void Path::Draw()
{
	if(loop)
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_LINE_STRIP);
	for(int i = 0; i  < numPoints; i++)
		glVertex2fv(points[i]);
	glEnd();
}