#pragma once

#include "stdincludes.h"

#include "Vector2.h"
#include "Color4f.h"
#include "renderer.h"
#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent(Entity *owner) : Component(owner) { z = 0; }
	virtual ~RenderComponent(void) { }


	virtual void Update(float deltaTime) { }
	virtual void Draw() { }

	int GetZ() const { return z; }

protected:
	int z;
};
