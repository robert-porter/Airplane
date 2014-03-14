#include "StraightPathMovementComponent.h"
#include "Entity.h"
#include "Vector2.h"

StraightPathMovementComponent::StraightPathMovementComponent(Entity *owner, float linearSpeed) : MovementComponent(owner)
{
	name = "StraightPathMovement";
	speed = linearSpeed;
}

StraightPathMovementComponent::~StraightPathMovementComponent()
{
}

void StraightPathMovementComponent::Update(float deltaTime)
{
	GetOwner()->transform.Translate( speed * deltaTime * GetOwner()->transform.GetUp() );
}
