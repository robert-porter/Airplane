#pragma once

#include "stdincludes.h"

#include "Vector2.h"
#include "Matrix2x2.h"


class Camera
{
public:
	Camera(void);
	~Camera(void);

	enum CameraType { CT_FIRST_PERSON, CT_THIRD_PERSON };

	void SetFrame(const Vector2 &pos, const float &rot)
	{
		position = pos;

		if(type == CT_FIRST_PERSON)
			rotation = rot;
		else
			rotation = 0.0f;
	}

	void SetType(CameraType t) { type = t; }
	CameraType GetType() const { return type; }

	Vector2		position;
	float		rotation;
	Vector2		extents;
	CameraType	type;
};
