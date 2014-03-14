#pragma once

#include "stdincludes.h"

#include "MovementComponent.h"
#include "Vector2.h"
#include "Timer.h"
#include "MathUtils.h"
#include "Transform.h"

class entity;

class BasicAirplaneMovementComponent : public MovementComponent
{
public:
				BasicAirplaneMovementComponent(Entity *owner, float linSpeed, float angSpeed);
				~BasicAirplaneMovementComponent(void);
	void		Update(float deltaTime);
	void		ThrustForward() ;
	void		ThrustBackward() ;
	void		ThrustLeft() ;
	void		ThrustRight();
	void		TurnCW() { angularVelocity -= angularSpeed; }
	void		TurnCCW() { angularVelocity += angularSpeed; }
	void        TurnTowardsTarget(const Vector2 &target);

	Vector2		GetVelocity() const { return velocity; }
	float		GetAngularVelocity() const { return angularVelocity; }
	//void		SetAngularVelocity(float w) { angularVelocity = w; }
protected:
	float		linearSpeed;
	float		angularSpeed;
	Vector2		velocity;
	float		angularVelocity;
};
