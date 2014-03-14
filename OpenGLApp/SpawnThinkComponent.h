#pragma once

#include "ThinkComponent.h"


class SpawnThinkComponent : public ThinkComponent
{
public:
	SpawnThinkComponent(Entity *owner);
	void Update(float deltaTime);
private:

	float spawnDelay;
	float timeAccum;
	float spreadX;
	int nMin, nMax;
};