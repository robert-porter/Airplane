#pragma once

#include "CollisionComponent.h"
#include "b2BroadPhase.h"


class CollisionSubsystem
{
public:
	CollisionSubsystem(void);
	~CollisionSubsystem(void);


	void Clear();
	void Add(CollisionComponent *c);
	void Test();


	b2BroadPhase broadPhase;

};
