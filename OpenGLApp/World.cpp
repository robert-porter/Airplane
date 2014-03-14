#include "World.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "timer.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "ThinkComponent.h"
#include "Gun.h"
#include "Airplane.h"
#include "Bullet.h"
#include "Powerup.h"

World::World(void)
{
	EntityFactory::SetWorld(this);

	entities.reserve(1000);
	doesDamage.reserve(1000);
	takesDamage.reserve(1000);
	hasGuns.reserve(1000);
	powerups.reserve(100);
}

World::~World(void)
{
	entities.clear();
}

void World::AddEntity(Entity * e) 
{ 
	entities.push_back(e); 
}  


void World::Update()
{
	if(GetAsyncKeyState(VK_SPACE))
		if ( dude->IsValid() )
			dude->Fire(0);

	for (unsigned int i = 0; i < entities.size(); i++ )
		if ( entities[i]->IsValid() )
		{
			ThinkComponent *thinkComponent = (ThinkComponent *) entities[i]->think;
			if(thinkComponent)
				thinkComponent->Update(FrameTimer::DeltaTime());
		}
	for (unsigned int i = 0; i < entities.size(); i++ )
		if ( entities[i]->type == ET_GUN && entities[i]->IsValid() )
		{
			Gun *gun = (Gun *) entities[i];
			gun->Update(FrameTimer::DeltaTime());
		}

	for (unsigned int i = 0; i < entities.size(); i++ )
		if ( entities[i]->IsValid() )
		{
			MovementComponent *movementComponent = (MovementComponent *) entities[i]->movement;
			if(movementComponent)
				movementComponent->Update(FrameTimer::DeltaTime());
		}


	doesDamage.clear();
	takesDamage.clear();
	hasGuns.clear();
	powerups.clear();

	for(unsigned int i = 0; i < entities.size(); i++)
	{
		if(entities[i]->type == ET_AIRPLANE)	
			takesDamage.push_back((Airplane *) entities[i]);
		if (entities[i]->type == ET_BULLET)
			doesDamage.push_back((Bullet *) entities[i]);
		if (entities[i]->type == ET_AIRPLANE && entities[i]->IsValid())
			hasGuns.push_back((Airplane *) entities[i]);
		if (entities[i]->type == ET_POWERUP && entities[i]->IsValid())
			powerups.push_back((Powerup *) entities[i]);
	}


	for(unsigned int i = 0; i < hasGuns.size(); i++)
	{
		for(unsigned int j = 0; j < powerups.size(); j++)
		{
			if (hasGuns[i]->team == powerups[j]->team)
			{
				CollisionComponent *iCollision = (CollisionComponent *)hasGuns[i]->shape;
				CollisionComponent *jCollision = (CollisionComponent *)powerups[j]->shape;

				if(iCollision->IntersectShape(jCollision))
				{
					powerups[j]->Touch(hasGuns[i]);
				}
			}
		}   
	}

	for(unsigned int i = 0; i < doesDamage.size(); i++)
	{
		for(unsigned int j = 0; j < takesDamage.size(); j++)
		{
			if (doesDamage[i]->team != takesDamage[j]->team)
			{
				CollisionComponent *iCollision = (CollisionComponent *)doesDamage[i]->shape;
				CollisionComponent *jCollision = (CollisionComponent *)takesDamage[j]->shape;
				if(iCollision->IntersectShape(jCollision))
				{
					takesDamage[j]->Touch(doesDamage[i]);
					doesDamage[i]->Touch(takesDamage[j]);
				}
			}
		}   
	}



	for(unsigned int i = 0; i < entities.size();i++)
	{

		if(!entities[i]->IsValid() && entities[i] != dude)
		{
			Entity*  p = entities[i];
			entities[i] = entities[entities.size() - 1];
			entities.pop_back();
		}
	}

}

