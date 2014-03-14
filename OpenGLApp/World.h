#pragma once

#include "stdincludes.h"
#include "Entity.h"
#include "CollisionSubsystem.h"


class Entity;

class World
{
public:
							World(void);
							~World(void);

	void					Update();
	void					AddEntity(Entity * e);

	Airplane*				dude;


	std::vector<Entity * >	entities;


	std::vector<Bullet * >	   doesDamage;
	std::vector<Airplane * >   takesDamage;
	std::vector<Airplane * >   hasGuns;
	std::vector<Powerup * >    powerups;

	CollisionSubsystem collisionSubsystem;

	Vector2 boundsMin, boundsMax;
};
