#pragma once

#include "stdincludes.h"

#include "Vector2.h"
#include "Entity.h"

class World;
class Entity;
class MovementComponent;




class EntityFactory
{
public:
	static void		SetWorld(World *w);
	static World    *GetWorld() { return world; }

	static Bullet*	CreatePlasmaParticle(Vector2 initialPosition, float initialAngle, int team);
	static Bullet*	CreateHomingMissle(Vector2 initialPosition, float initialAngle, int team);
	static Bullet*	CreateLaser(Vector2 initialPosition, float initialAngle, int team);
	static Bullet*	CreateBasicBullet(Vector2 initialPosition, float initialAngle, int team);
//	static Entity*  CreateCannonBullet(Vector2 initialPosition, float initialAngle, int team);
//  static Entity*  CreateBomb(Vector2 initialPosition, float initialAngle, int team);

	static float	GetFireDelay(BULLET_TYPE);
	static Bullet*  CreateBullet(BULLET_TYPE, const Vector2 &initialPosition, float initialAngle, int team);
	static Powerup*  CreateRandomPowerup(const Vector2 &initialPosition, float initialAngle, int team);
	static Airplane*	CreatePlayer(const Vector2& initialPosition, float initialAngle);

	static Airplane*  CreateBasicEnemy(const Vector2& initialPosition, float initialAngle);
	static Airplane*  CreateEnemy0(const Vector2& initialPosition, float initialAngle);
	static Airplane*  CreateEnemy1(const Vector2& initialPosition, float initialAngle);
//	static Entity*	CreateEnemy2(const Vector2& initialPosition, float initialAngle);

	static Entity*  CreateSmallExplosion(const Vector2 &initialPosition, float initialAngle);
	static Entity*  CreateBigExplosion(const Vector2 &initialPosition, float initialAngle);
	
	static Gun*  CreateGun(int team);
	static Powerup*  CreatePowerup(const Vector2 &initialPosition, float initialAngle, int team);

	static Entity*  CreateBounds(float radius);
	static Entity*  CreateSpawner();

	static Entity*  CreateExhaustParticleSystem();
	static Entity*  CreateBackground();
private:
	static World*	world;
};
	