#pragma once

#include "stdincludes.h"

#include "rendercomponent.h"

class ParticleSystemRenderComponent : public RenderComponent
{
public:
	ParticleSystemRenderComponent(Entity *owner);
	~ParticleSystemRenderComponent(void);

	void Update(float deltaTime);
	void Draw();

	struct Particle
	{
		Vector2 position;
		Vector2 velocity;
		Vector2 acceleration;
		float	size0;
		float	angle0;
		Color4f color0;
		float	age;
		float	lifetime;
	};

	Particle *particles;
	int maxNumParticles;
	int numLiveParticles;


	GLuint		texture;

	float		spawnDelay;
	float       timeAccum;

	float       particleLifeMin;
	float       particleLifeMax;

	float       emitAngle;
	float       emitSpread;

	float       speedMin;
	float       speedMax;

	float       radialAccelMin;
	float       radialAccelMax;

	float       tangentialAccelMin;
	float       tangentialAccelMax;

	float       sizeStart;
	float       sizeEnd;
	float       sizeVar;


	float       angleStart;
	float       angleEnd;
	float       angleVar;

	Color4f     colorStart;
	Color4f     colorEnd;
	float       colorVar;
	float       alphaVar;

};
