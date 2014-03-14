#pragma once

#include "stdincludes.h"
#include "Component.h"


class Gun;
class Entity;
class MovementComponent;
class BasicAirplaneMovementComponent;

class ThinkComponent : public Component
{
public:
	ThinkComponent(Entity *owner) : Component(owner) { familyName = "Think"; }
	virtual ~ThinkComponent(void);

	virtual void Update(float deltaTime) = 0;
protected:
};

class KeyboardControlledThinkComponent : public ThinkComponent
{
public:
	KeyboardControlledThinkComponent(Entity *owner, BasicAirplaneMovementComponent* m, Gun *g) : ThinkComponent(owner), move(m), gun(g), time(0), toggleDelay(0.3) { }
	~KeyboardControlledThinkComponent() { }
	void Update(float deltaTime);
private:
	BasicAirplaneMovementComponent *move;
	Gun *gun;
	float time;
	float toggleDelay;
};


class HomingThinkComponent : public ThinkComponent
{
public:
	HomingThinkComponent(Entity *owner);
	~HomingThinkComponent();
	void Update(float deltaTime);

	void SetTarget(Entity * e);


	void SetMovementComponent(BasicAirplaneMovementComponent *m);
private:
	Entity * target;
	BasicAirplaneMovementComponent *movement;
};




class TimedDeletionThinkComponent : public ThinkComponent
{
public:
	TimedDeletionThinkComponent(Entity *owner);
	
	void Update(float deltaTime);
private:
	float timeAccum;
	float lifetime;
};

class ShootForwardThinkComponent : public ThinkComponent
{
public:
	ShootForwardThinkComponent(Entity *owner, Gun *g) : ThinkComponent(owner), gun(g) { }
	void Update(float deltaTime);
private:
	Gun *gun;
};