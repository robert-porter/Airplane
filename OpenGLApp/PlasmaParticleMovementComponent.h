#pragma once

#include "stdincludes.h"

#include "MovementComponent.h"
#include "Vector2.h"

class PlasmaParticleMovementComponent : public MovementComponent
{
public:
				PlasmaParticleMovementComponent(Entity *owner, float linearSpeed, float amp, float freq);
				~PlasmaParticleMovementComponent(void);
	void		Update(float deltaTime);
private:
	float		speed;
	float		amplitude;
	float		time;
	float		k;
	float		w0;	
};


