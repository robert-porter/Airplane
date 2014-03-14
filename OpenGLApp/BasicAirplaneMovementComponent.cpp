#include "BasicAirplaneMovementComponent.h"
#include "Entity.h"

BasicAirplaneMovementComponent::BasicAirplaneMovementComponent(Entity *owner, float linSpeed, float angSpeed) : MovementComponent(owner)
{
	velocity.Set(0,0);
	angularVelocity = 0;
	linearSpeed = linSpeed;
	angularSpeed = angSpeed;
}

BasicAirplaneMovementComponent::~BasicAirplaneMovementComponent(void)
{
}


void BasicAirplaneMovementComponent::Update(float deltaTime)
{
	GetOwner()->transform.Translate( deltaTime * velocity ); 
	GetOwner()->transform.RotateCCW( deltaTime * angularVelocity );
	velocity.Set(0.0f, 0.0f);
	angularVelocity = 0.0f;
}

void BasicAirplaneMovementComponent::TurnTowardsTarget(const Vector2 &target) 
{ 
	Vector2 v = target - GetOwner()->transform.GetPosition();

	Vector2 vPerp(v.y, -v.x);
	float a = Dot(GetOwner()->transform.GetUp(),vPerp);
	float newRotation;
	if(a < 0.0f)
	{ 
		newRotation = GetOwner()->transform.GetRotation() + angularSpeed * FrameTimer::DeltaTime();
		a = Dot(Vector2(-sinf(newRotation),cosf(newRotation)),vPerp);
		if ( a > 0.0f )
			GetOwner()->transform.SetRotation( atan2f(v.y, v.x) + 0.5f * PI );
		else TurnCW();
	}
	else
	{
		newRotation = GetOwner()->transform.GetRotation() - angularSpeed * FrameTimer::DeltaTime();
		a = Dot(Vector2(-sinf(newRotation),cosf(newRotation)),vPerp);
		if ( a < 0.0f )
			GetOwner()->transform.SetRotation( atan2f(v.y, v.x) + 0.5f * PI );
		else TurnCCW();

	}
}

void    BasicAirplaneMovementComponent::ThrustForward() { velocity += linearSpeed * GetOwner()->transform.GetUp(); }
void    BasicAirplaneMovementComponent::ThrustBackward() { velocity -= linearSpeed * GetOwner()->transform.GetUp(); }
void	BasicAirplaneMovementComponent::ThrustLeft() { velocity += linearSpeed * -GetOwner()->transform.GetRight(); }
void	BasicAirplaneMovementComponent::ThrustRight() { velocity += linearSpeed * GetOwner()->transform.GetRight(); }