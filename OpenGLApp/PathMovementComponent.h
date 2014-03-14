#pragma once

#include "Path.h"
#include "MovementComponent.h"

class PathMovementComponent : public MovementComponent
{
public:
				PathMovementComponent(Entity *owner, float linearSpeed);
		//		PathMovementComponent(TiXmlElement *xmlElement);
				~PathMovementComponent();
	void		Update(float deltaTime);	
private:
	float		time;
	Vector2		direction;
	float		speed;

	Path *path;
};
