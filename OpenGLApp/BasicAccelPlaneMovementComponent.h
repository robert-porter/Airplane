#pragma once

#include "stdincludes.h"

#include "BasicAirplaneMovementComponent.h"


class BasicAccelPlaneMovementComponent : public BasicAirplaneMovementComponent
{
public:

	~BasicAccelPlaneMovementComponent(void);

	BasicAccelPlaneMovementComponent(Entity *owner, float linSpeed, float angSpeed) : BasicAirplaneMovementComponent(owner, linSpeed, angSpeed)
	{
		time = 0;
	}



	void BasicAccelPlaneMovementComponent::Update(float deltaTime);

	float time;
	float maxSpeed;
};
