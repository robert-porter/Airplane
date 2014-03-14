#include "ThinkComponent.h"
#include "Entity.h"
#include "BasicAirplaneMovementComponent.h"
#include "World.h"
#include "StraightPathMovementComponent.h"
#include "EntityFactory.h"
#include "Gun.h"

#include <vector>

enum INPUT_ACTION 
{
	IA_NONE,
	IA_FORWARD,
	IA_BACKWARD,
	IA_LEFT,
	IA_RIGHT,
	IA_TURN_LEFT,
	IA_TURN_RIGHT,
	IA_FIRE,
	IA_TOGGLE_BULLET_TYPE,
	IA_TOGGLE_MULTI_SHOT, 
	IA_TOGGLE_RAPID_SHOT,
	IA_TOGGLE_SPREAD_SHOT

};


ThinkComponent::~ThinkComponent(void)
{
}
void KeyboardControlledThinkComponent::Update(float deltaTime)
{
	time += deltaTime;


	std::vector<INPUT_ACTION> input;
	if(GetAsyncKeyState('A'))
		input.push_back(IA_LEFT);
	if(GetAsyncKeyState('D'))
		input.push_back(IA_RIGHT);
	if(GetAsyncKeyState('W'))
		input.push_back(IA_FORWARD);
	if(GetAsyncKeyState('S'))
		input.push_back(IA_BACKWARD);
	if(GetAsyncKeyState(VK_SPACE))
		input.push_back(IA_FIRE);
	if(time >= toggleDelay)
	{
		time -= toggleDelay;

		if(GetAsyncKeyState('P'))
			input.push_back(IA_TOGGLE_BULLET_TYPE);
		if(GetAsyncKeyState('O'))
			input.push_back(IA_TOGGLE_MULTI_SHOT);
		if(GetAsyncKeyState('I'))
			input.push_back(IA_TOGGLE_RAPID_SHOT);
		if(GetAsyncKeyState('U'))
			input.push_back(IA_TOGGLE_SPREAD_SHOT);

	}
	
	for ( unsigned int i = 0; i < input.size(); i++ )
	{
		switch ( input[i] )
		{
		case IA_FORWARD:
			{
			move->ThrustForward();
			break;
			}
		case IA_BACKWARD:
			{
			move->ThrustBackward();
			break;
			}
		case IA_LEFT:
			{
			move->ThrustLeft();
			break;
			}
		case IA_RIGHT:
			{
			move->ThrustRight();
			break;
			}
		case IA_TURN_LEFT:
			move->TurnCCW();
			break;
		case IA_TURN_RIGHT:
			move->TurnCW();
			break;
		case IA_FIRE:
			gun->AttemptToFire();
			break;
		case IA_TOGGLE_BULLET_TYPE:
			gun->ToggleBulletType();
			break;
		case IA_TOGGLE_MULTI_SHOT:
			gun->ToggleMultiShot();
			break;
		case IA_TOGGLE_RAPID_SHOT:
			gun->ToggleRapidShot();
			break;
		case IA_TOGGLE_SPREAD_SHOT:
			gun->ToggleSpreadShot();
			break;
		}
	}
}
HomingThinkComponent::HomingThinkComponent(Entity *owner) : ThinkComponent(owner)
{

}
HomingThinkComponent::~HomingThinkComponent()
{
}

void HomingThinkComponent::SetTarget(Entity* e)
{
	target = e;
}

void HomingThinkComponent::SetMovementComponent(BasicAirplaneMovementComponent *m)
{
	movement = m;
}

void HomingThinkComponent::Update(float deltaTime)
{
    if(target)
	{
		if(!target->IsValid())
		{
		}
		else
		{
            movement->TurnTowardsTarget(target->transform.GetPosition()); 
		}
	} 

	movement->ThrustForward();
}

TimedDeletionThinkComponent::TimedDeletionThinkComponent(Entity *owner) : ThinkComponent(owner)
{ 
	timeAccum = 0.0f; 
	lifetime = 0.2f; 
}

void TimedDeletionThinkComponent::Update(float deltaTime) 
{ 
	timeAccum += deltaTime; 
	if(timeAccum > lifetime) 
	{
		owner->Invalidate(); 
	}
}

void ShootForwardThinkComponent::Update(float deltaTime)
{
	gun->AttemptToFire();
}