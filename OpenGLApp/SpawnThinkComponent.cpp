#include "SpawnThinkComponent.h"
#include "Entity.h"
#include "EntityFactory.h"

SpawnThinkComponent::SpawnThinkComponent(Entity *owner) : ThinkComponent(owner)
{
	timeAccum = 0.0f;
	spawnDelay = 1.0f;
	spreadX = 3.0f;
	nMin = 0;
	nMax = 4;
}


void SpawnThinkComponent::Update(float deltaTime) 
{
	Transform *transform = &GetOwner()->transform;

	timeAccum += deltaTime;

	if(timeAccum >= spawnDelay)
	{
		int n = rand() % 4;
		timeAccum -= spawnDelay;
		
		if(n == 1)
		{
			float offsetX = spreadX * 0.5f;
			EntityFactory::CreateBasicEnemy(transform->GetPosition(), PI);
			EntityFactory::CreateEnemy1(transform->GetPosition() + Vector2(offsetX, 0.0f), PI);
			EntityFactory::CreateEnemy1(transform->GetPosition() - Vector2(offsetX, 0.0f), PI);
		}
		else if(n == 2)
		{
			float offsetX = spreadX * 0.5f;
			EntityFactory::CreateBasicEnemy(transform->GetPosition(), PI);
			EntityFactory::CreateEnemy1(transform->GetPosition() + Vector2(offsetX, 0.0f), PI);
			EntityFactory::CreateEnemy1(transform->GetPosition() - Vector2(offsetX, 0.0f), PI);
		}
		else if(n == 3)
		{
			float offsetX = spreadX * 0.5f;
			EntityFactory::CreateBasicEnemy(transform->GetPosition(), PI);
			EntityFactory::CreateEnemy0(transform->GetPosition() + Vector2(offsetX, 0.0f), PI);
			EntityFactory::CreateEnemy0(transform->GetPosition() - Vector2(offsetX, 0.0f), PI);
		}
	}

}