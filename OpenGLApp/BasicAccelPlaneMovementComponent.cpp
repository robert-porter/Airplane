#include "BasicAccelPlaneMovementComponent.h"
#include "Entity.h"

BasicAccelPlaneMovementComponent::~BasicAccelPlaneMovementComponent(void)
{
}

void BasicAccelPlaneMovementComponent::Update(float deltaTime)
{
	time += deltaTime;

	maxSpeed = 10.0f;
	if ( linearSpeed > maxSpeed )
		linearSpeed = maxSpeed; 
	else
	{
		float b = 10.0f;
		float a = 0.0f;
		linearSpeed = a*time + b;
	}

	GetOwner()->transform.Translate( deltaTime * velocity );
	GetOwner()->transform.RotateCCW( deltaTime * angularVelocity );
	velocity.Set(0.0f, 0.0f);
	angularVelocity = 0.0f;
}