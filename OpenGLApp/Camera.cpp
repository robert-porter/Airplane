#include "Camera.h"

Camera::Camera(void)
{
	position.Set(0.0f,0.0f);
	rotation = 0.0f;
	extents.Set(4.0f, 4.0f);


	type = CT_THIRD_PERSON;
}

Camera::~Camera(void)
{
}
