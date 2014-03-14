#pragma once

#include <vector>

#include "stdincludes.h"

#include "Vector2.h"
#include "MathUtils.h"
#include "matrix2x2.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "ThinkComponent.h"
#include "CollisionComponent.h"

enum ENTITY_TYPE
{
	ET_NONE,
	ET_AIRPLANE,
	ET_BULLET,
	ET_POWERUP,
	ET_GUN,
	ET_EFFECT
};

enum BULLET_TYPE
{
	BT_BASIC_BULLET,
	BT_PLASMA,
	BT_HOMING_MISSLE,
	BT_LASER,
	BT_NUM_TYPES
};

enum TEAM_TYPE
{
	TT_TEAM_PLAYER,
	TT_TEAM_ENEMY,
	TT_TEAM_NUETRAL
};

enum BOUNDS_MODE
{
	BM_CLAMP,
	BM_WRAP,
	BM_KILL,
	BM_NONE
};

class Airplane;
class Gun;
class Bullet;
class Powerup;
class Effect;

class Entity
{
public:


							Entity(void);
							~Entity(void);

	void					AddChild(Entity * child);
	bool                    IsValid() const;
	void                    Invalidate();
		
	const std::string &     GetName() const;
	void					SetName(const std::string &n);

	ENTITY_TYPE				type;
	std::string				name;
	int						team;
	bool					valid;
	Transform               transform;
	RenderComponent         *visual;
	CollisionComponent      *shape;
	MovementComponent       *movement;
	ThinkComponent          *think;

	//typedef std::map<std::string, Component *>::iterator MapIter;
	//std::map<std::string, Component *> components;

	std::vector<Entity * >	children; // these are invalidated with the parent


};
