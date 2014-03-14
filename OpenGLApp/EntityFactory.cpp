#include "EntityFactory.h"
#include "Entity.h"
#include "StraightPathMovementComponent.h"
#include "BasicAirplaneMovementComponent.h"
#include "PlasmaParticleMovementComponent.h"
#include "ThinkComponent.h"
#include "World.h"
#include "ParticleSystemRenderComponent.h"
#include "BasicAccelPlaneMovementComponent.h"
#include "StaticSpriteRenderComponent.h"
#include "AnimatedSpriteRenderComponent.h"
#include "SpawnThinkComponent.h"
#include "CollisionComponent.h"
#include "Renderer.h"
#include "PathMovementComponent.h"
#include "transform.h"
#include "Airplane.h"
#include "Bullet.h"
#include "Effect.h"
#include "Gun.h"
#include "Powerup.h"

World* EntityFactory::world = 0;


void EntityFactory::SetWorld(World *w)
{
	world = w;
}

Bullet* EntityFactory::CreateBullet(BULLET_TYPE bulletType, const Vector2 &initialPosition, float initialAngle, int team)
{
	if(bulletType == BT_BASIC_BULLET)
		return CreateBasicBullet(initialPosition, initialAngle, team);
	else if(bulletType == BT_PLASMA)
		return CreatePlasmaParticle(initialPosition, initialAngle, team);
	else if(bulletType == BT_HOMING_MISSLE)
		return CreateHomingMissle(initialPosition, initialAngle, team);
	else if(bulletType == BT_LASER)
		return CreateLaser(initialPosition, initialAngle, team);
	else
	{
		assert(false);
		std::cout<<"EntityFactory::CreateBullet: Using undefined BULLET_TYPE"<<std::endl;
		return 0;
	}
}

float EntityFactory::GetFireDelay(BULLET_TYPE bulletType)
{	
	if(bulletType == BT_BASIC_BULLET)
		return 0.3f;
	else if(bulletType == BT_PLASMA)
		return 0.01f;
	else if(bulletType == BT_HOMING_MISSLE)
		return 1.f;
	else if(bulletType == BT_LASER)
		return 0.6f;
	else
	{
		assert(false);
		std::cout<<"EntityFactory::GetFireDelay: Using undefined BULLET_TYPE"<<std::endl;
		return 0.0f;
	}
}


Bullet*	EntityFactory::CreateBasicBullet(Vector2 initialPosition, float initialAngle, int team)
{
	
	std::string		name			=	"BasicBullet0";
	std::string		texure			=	"bullet.png";
	float			textureWidth	=	0.25f;
	float			textureHeight	=	0.25f;
	float			linearSpeed		=	15.0f;
	float			collisionRadius =	0.2f;
	float			damageDealt		=	10.0f;
	float			health			=	1.0f;

	assert(world);
	Bullet * bullet = new Bullet;
	bullet->SetName(name);
	bullet->team = team;
	bullet->visual = new StaticSpriteRenderComponent(bullet, Renderer::GetTexture(texure), textureWidth, textureHeight, 10);
	bullet->shape = new CollisionCircle(bullet, collisionRadius);
	bullet->movement = new StraightPathMovementComponent(bullet, linearSpeed);
	bullet->damage = 20.0f;
	bullet->transform.Set(initialPosition, initialAngle, 1.0f);
	bullet->team = team;
	world->AddEntity(bullet);
	
	return bullet;
}
Bullet* EntityFactory::CreatePlasmaParticle(Vector2 initialPosition, float initialAngle, int team)
{

	assert( world );
	Bullet * bullet = new Bullet;
	bullet->transform.Set(initialPosition, initialAngle, 1.0f);
	bullet->SetName("PlasmaParticle");
	bullet->team = team;
	bullet->visual = new StaticSpriteRenderComponent(bullet, Renderer::GetTexture("particle.png"), 0.1f, 0.1f, 5);

	float brightness = 1.0f;
	float r = Random();
	float g = Random();
	float b = Random();
	float l = sqrtf(r*r + g*g + b*b);
	r/=l;
	g/=l;
	b/=l;
	r*=brightness;
	g*=brightness;
	b*=brightness;
	StaticSpriteRenderComponent* x = (StaticSpriteRenderComponent*)(bullet->visual);
	x->tint = Color4f(r, g, b, 1.0f);
	bullet->movement = new PlasmaParticleMovementComponent(bullet, 13.0f, 0.3f, 4.0f );
	bullet->shape = new CollisionCircle(bullet, 0.1f);
	bullet->damage = 10.0f;
	world->AddEntity( bullet );
	

	return bullet;
}

Bullet* EntityFactory::CreateHomingMissle(Vector2 initialPosition, float initialAngle, int team)
{
	assert(world);
	Bullet * bullet = new Bullet;
	bullet->SetName("HomingMissle");
	bullet->transform.Set(initialPosition, initialAngle, 2.0f);
	bullet->team = team;
	bullet->visual = new StaticSpriteRenderComponent(bullet, Renderer::GetTexture("missle.png"), 0.05f, 0.4f, 5);
	BasicAirplaneMovementComponent *move = new BasicAccelPlaneMovementComponent(bullet, 7.0f, 3.0f);
	HomingThinkComponent *think = new HomingThinkComponent(bullet);
	think->SetMovementComponent(move);
	
	bool targetFound = false;
	int minIndex = 0;
	float minD = INFINITY;
	for(unsigned int i = 0; i < world->entities.size(); i++)
	{
		if(world->entities[i]->IsValid() && world->entities[i]->type == ET_AIRPLANE && world->entities[i]->team != team)
		{
			targetFound = true;
			float d = (world->entities[i]->transform.GetPosition() - initialPosition).SquaredLength();
			if(d < minD)
			{
				minIndex = i;
				minD = d;
			}
		}
	}
	if(!targetFound)
	{
//	think->SetTarget(0);
	}
	else
	{

		think->SetTarget(world->entities[minIndex]);
	}
	bullet->movement = move;
	bullet->think = think;
	bullet->shape = new CollisionCapsule(bullet, Vector2(0, -0.1f), Vector2(0.0f, 0.1f), 0.025f);
	bullet->damage = 100.0f;

	Entity *  exhaust = CreateExhaustParticleSystem();
	exhaust->transform.Set(Vector2(0.0f,-0.3f), 0.0f, 1.0f, &bullet->transform);
	bullet->AddChild(exhaust);

	world->AddEntity(bullet);
	return bullet;
}

Bullet* EntityFactory::CreateLaser(Vector2 initialPosition, float initialAngle, int team)
{
	assert(world);
	Bullet * bullet = new Bullet;
	bullet->SetName("Laser");
	bullet->team = team;
	bullet->transform.Set(initialPosition, initialAngle, 1.0f);
	StaticSpriteRenderComponent *renderComponent = new StaticSpriteRenderComponent(bullet, Renderer::GetTexture("laser.png"), 1.0f, 1.0f, 5);
	renderComponent->rotationCenter = Vector2(0, -renderComponent->height/2.0f);
	renderComponent->positionAnchor = Vector2(0, -renderComponent->height/2.0f);
	bullet->visual = renderComponent;
	bullet->movement = new StraightPathMovementComponent(bullet, 18.0f);
	bullet->damage = 20.0f;
	bullet->shape = new CollisionCapsule(bullet, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.7f), 0.025f);
	world->AddEntity(bullet);
	return bullet;
}

Airplane* EntityFactory::CreatePlayer(const Vector2& initialPosition, float initialAngle)
{
	Airplane * e = new Airplane;
	e->SetName("Player");
	e->team = 0;
	e->transform.Set(initialPosition, initialAngle, 1.0f);
	BasicAirplaneMovementComponent *move = new BasicAirplaneMovementComponent(e, 5.0f, 0.7f);
	e->movement = (move);
	e->visual = ( new StaticSpriteRenderComponent(e, Renderer::GetTexture("B-3a.png"), 1.0f, 1.0f, 10) );
	e->health = 100.0f;
	e->maxHealth = 100.0f;
	e->lives = 9999;
	e->shape = (new CollisionCircle(e, 0.43f) );


	Gun * g1 = CreateGun(0);
	g1->transform.SetIdentity();
	g1->transform.SetParent(&e->transform);
	e->AddGun(g1);
	e->AddChild(g1);

	e->think = ( new KeyboardControlledThinkComponent(e, move, g1 ) );
	//e->AddComponent( new DamagingComponent(100.0f, false) );
	world->AddEntity(e);

	Entity * exhaust = CreateExhaustParticleSystem();
	exhaust->transform.Set(Vector2(0.0f, -0.3f), 0.0f, 1.0f, &e->transform);
	e->AddChild(exhaust);

	return e;
}

Airplane* EntityFactory::CreateBasicEnemy(const Vector2& initialPosition, float initialAngle)
{
	Airplane * e = new Airplane;
	e->SetName("BasicEnemy");
	e->team = 1;
	e->transform.Set(initialPosition, initialAngle, 1.0f);
	e->movement = ( new StraightPathMovementComponent(e, 3.0f) );


	e->visual = ( new StaticSpriteRenderComponent(e, Renderer::GetTexture("B-3a.png"), 1.0f, 1.0f, 9) );
	e->health = 30.0f;
	e->maxHealth = 30.0f;
	e->shape = ( new CollisionCircle(e, 0.43f) );
//	e->AddComponent( new DamagingComponent(10.0f, false) );

	Gun * g1 = CreateGun(1);
	g1->transform.SetIdentity();
	g1->transform.SetParent(&e->transform);
	e->AddGun(g1);
	e->AddChild(g1);
	e->think = ( new ShootForwardThinkComponent(e, g1) );

	Entity * exhaust = CreateExhaustParticleSystem();
	exhaust->transform.Set(Vector2(0.0f, -0.3f), 0.0f, 1.0f, &e->transform);
	e->AddChild(exhaust);

	world->AddEntity(e);

	return e;
}

Airplane*	EntityFactory::CreateEnemy0(const Vector2& initialPosition, float initialAngle)
{
	Airplane * e = new Airplane;
	e->SetName("Enemy0");
	e->team = 1;
	e->transform.Set(initialPosition, initialAngle, 1.0f);
	e->movement = (new StraightPathMovementComponent(e, 3.0f));


	e->visual = ( new StaticSpriteRenderComponent(e, Renderer::GetTexture("SR-91A.png"), 0.6, 0.6, 9) );
	e->health = 30.0f;
	e->maxHealth = 30.0f;
	e->shape = ( new CollisionCircle(e, 0.38f));
//	e->AddComponent( new DamagingComponent(10.0f, false) );

	Gun * g1 = CreateGun(1);
	e->AddGun(g1);
	e->AddChild(g1);

	Entity * exhaust = CreateExhaustParticleSystem();
	exhaust->transform.Set(Vector2(0.0f, -0.3f), 0.0f, 1.0f, &e->transform);
	e->AddChild(exhaust);

	world->AddEntity(e);

	return e;
}

Airplane*	EntityFactory::CreateEnemy1(const Vector2& initialPosition, float initialAngle)
{
	Airplane * e = new Airplane;
	e->SetName("Enemy1");
	e->team = 1;
	e->transform.Set(initialPosition, initialAngle, 1.0f);
	e->movement = (new BasicAirplaneMovementComponent(e, 3.0f, 2.0));
	e->visual = ( new StaticSpriteRenderComponent(e, Renderer::GetTexture("SR-91A.png"), 0.6, 0.6, 9) );
	e->health = 30.0f;
	e->maxHealth = 30.0f;
	e->shape = ( new CollisionCircle(e, 0.38f));
	HomingThinkComponent *think = new HomingThinkComponent(e);
	think->SetMovementComponent((BasicAirplaneMovementComponent *) e->movement);
	think->SetTarget(world->dude);
	e->think = think;
	Gun * g1 = CreateGun(1);
	e->AddGun(g1);
	e->AddChild(g1);

	Entity * exhaust = CreateExhaustParticleSystem();
	exhaust->transform.Set(Vector2(0.0f, -0.3f), 0.0f, 1.0f, &e->transform);
	e->AddChild(exhaust);

	world->AddEntity(e);

	return e;
}
Entity* EntityFactory::CreateSmallExplosion(const Vector2 &initialPosition, float initialAngle)
{
	Effect * e = new Effect;
	e->transform.Set( initialPosition, initialAngle, 1.0f );
	e->SetName("SmallExplosion");
	e->team = -1;
	//e->AddComponent( new AnimatedSpriteRenderComponent(textures, numFrames, 0.1f, 0.2f, 0.2f) );
	e->visual = ( new StaticSpriteRenderComponent(e, Renderer::GetTexture("smallExplosion.png"), 1.0f, 1.0f, 10));
	e->think = ( new TimedDeletionThinkComponent(e));
	world->AddEntity(e);
	return e;
}

Entity* EntityFactory::CreateBigExplosion(const Vector2 &initialPosition, float initialAngle)
{
	Effect * e = new Effect;
	e->SetName("BigExplosion");
	e->team = -1;
	GLuint textures[4];
	textures[0] = Renderer::GetTexture("smallExplosion.png");
	textures[1] = Renderer::GetTexture("bigExplosion.png");
	textures[2] = Renderer::GetTexture("particle.png");

	e->transform.Set(initialPosition, initialAngle, 1.0f );
	e->visual = ( new AnimatedSpriteRenderComponent(e, textures, 3, 0.1, 1.0f, 1.0f) );
	e->think = ( new TimedDeletionThinkComponent(e) );
	world->AddEntity(e);
	return e;
}

Gun * EntityFactory::CreateGun(int team)
{
	
	Gun * g1 = new Gun(team);
	g1->SetName("Gun");
	g1->team = team;
	g1->visual = new StaticSpriteRenderComponent(g1, Renderer::GetTexture("gun.bmp"), 0.4, 0.4f, 11);
	world->AddEntity(g1);
	return g1;
}

Powerup* EntityFactory::CreatePowerup(const Vector2 &initialPosition, float initialAngle, int team)
{
	Powerup * e = new Powerup;
	e->SetName("GunPowerUp");
	e->team = team;
	e->transform.Set(initialPosition, initialAngle, 1.0f);
	e->movement = new StraightPathMovementComponent(e, -0.6f);
	e->visual = new StaticSpriteRenderComponent(e, Renderer::GetTexture("powerup.png"), 1.0f, 1.0f, 4);
	e->shape = new CollisionCircle(e, 0.4f);
	world->AddEntity(e);
	return e;
}

Entity * EntityFactory::CreateBounds(float radius)
{
	Entity * e = new Entity;
	e->SetName("Bounds");
	e->team = 99;
	e->transform.SetIdentity();
	e->shape = new CollisionOutOfBounds(e, radius);
	world->AddEntity(e);

	return e;
}

Entity* EntityFactory::CreateSpawner()
{
	Entity * spawner = new Entity;
	spawner->transform.Set(Vector2(0.0f, 4.0f), 0.0f, 1.0f);
	spawner->think = new SpawnThinkComponent(spawner);
	world->AddEntity(spawner);
	return spawner;
}

Powerup* EntityFactory::CreateRandomPowerup(const Vector2 &initialPosition, float initialAngle, int team)
{
	Powerup * e = new Powerup;
	e->SetName("GunPowerUp");
	e->team = team;
	e->transform.Set(initialPosition, initialAngle, 1.0f);
	e->movement = new StraightPathMovementComponent(e, -0.6f);
	e->visual = new StaticSpriteRenderComponent(e, Renderer::GetTexture("powerup.png"), 0.5f, 0.5f, 4);
	e->shape = new CollisionCircle(e, 0.4f);
	e->SetRandom();

	world->AddEntity(e);
	return e;
}

Entity* EntityFactory::CreateExhaustParticleSystem()
{
	Effect * e = new Effect;

	e->SetName("ExhaustParticleSystem");
	ParticleSystemRenderComponent *ps = new ParticleSystemRenderComponent(e);
	
	ps->particles = 0;

	ps->texture = Renderer::GetTexture("particle.png");


	ps->timeAccum = 0.0f;

	ps->particleLifeMin = 0.1f;
	ps->particleLifeMax = 0.2f;

	ps->emitAngle = 1.5f * PI;
	ps->emitSpread = PI/4.0f;

	ps->speedMin = 1.0f;
	ps->speedMax = 2.0f;

	ps->radialAccelMin = -2.0f;
	ps->radialAccelMax = -4.0f;

	ps->tangentialAccelMin = 0.0f;
	ps->tangentialAccelMax = 0.0f;

	ps->sizeStart = 0.1f;
	ps->sizeEnd = 0.2f;
	ps->sizeVar = 0.8f;

	ps->angleStart = 0.0f;
	ps->angleEnd = 2.0f * PI;
	ps->angleVar = 0.1f;

	ps->colorStart = Color4f(1, 0.6f, 1.0f, 1.0f);
	ps->colorEnd = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
	ps->colorVar = 0.5f;
	ps->alphaVar = 0.2f;

	int particlesPerSecond = 50.0f;
	ps->spawnDelay = 1.0f / float(particlesPerSecond);
	ps->maxNumParticles = 100;
	ps->numLiveParticles = 0;

	ps->particles = new ParticleSystemRenderComponent::Particle[ps->maxNumParticles];
	e->visual = ( ps );

	world->AddEntity(e);
	return e;
}

Entity*  EntityFactory::CreateBackground()
{
	Effect * e = new Effect;
	e->SetName( "Background" );
	e->team = 0;
	e->transform.SetIdentity();
	e->movement = ( new StraightPathMovementComponent(e, -0.05f) );
	e->visual = ( new StaticSpriteRenderComponent(e, Renderer::GetTexture("stormClouds.png"), 20.0f, 20.0f, 0) );
	world->AddEntity( e );
	return e;
}