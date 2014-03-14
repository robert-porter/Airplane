#pragma once

#include "stdincludes.h"

#include "Vector2.h"
#include "Matrix2x2.h"
#include "Component.h"


class Entity;

class MovementComponent : public Component
{
public:
				 MovementComponent(Entity *owner) : Component(owner) {  }
	virtual		 ~MovementComponent() { }
	virtual void Update(float deltaTime) { };

};

