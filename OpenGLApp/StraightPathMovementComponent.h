#pragma once

#include "stdincludes.h"
#include "MovementComponent.h"
#include "Vector2.h"

class StraightPathMovementComponent : public MovementComponent
{
public:
			StraightPathMovementComponent(Entity *owner, float linearSpeed);
			~StraightPathMovementComponent();
	void	Update(float deltaTime);	
	void    SetSpeed(float newSpeed) { speed = newSpeed; }
	float   GetSpeed() const { return speed; }
private:
	float	speed;
};
