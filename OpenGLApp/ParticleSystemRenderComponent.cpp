#include "ParticleSystemRenderComponent.h"
#include "MovementComponent.h"
#include "Entity.h"


ParticleSystemRenderComponent::ParticleSystemRenderComponent(Entity *owner) : RenderComponent(owner)
{
}

ParticleSystemRenderComponent::~ParticleSystemRenderComponent(void)
{
	if(particles)
		delete []particles;
}

void ParticleSystemRenderComponent::Update(float deltaTime)
{
	timeAccum += deltaTime;
	if(timeAccum > spawnDelay && numLiveParticles <= maxNumParticles)
	{
		timeAccum -= spawnDelay;

		particles[numLiveParticles].position = Vector2(0.0f, 0.0f);
		particles[numLiveParticles].age = 0.0f;
		
		float a  = emitAngle + Random(-0.5f * emitSpread, 0.5f * emitSpread);
		Vector2 forward(cosf(a), sinf(a));
		Vector2 right(-forward.y, forward.x);

		particles[numLiveParticles].velocity = Random(speedMin, speedMax) * forward; 

		Vector2 acceleration = Random(radialAccelMin, radialAccelMax) * forward;
		if(rand() % 2)
			acceleration += Random(tangentialAccelMin, tangentialAccelMin) * right;
		else
			acceleration -= Random(tangentialAccelMin, tangentialAccelMin) * right;
		particles[numLiveParticles].acceleration = acceleration;
		particles[numLiveParticles].lifetime = Random(particleLifeMin, particleLifeMax);
		particles[numLiveParticles].size0 = (1.0f - sizeVar) * sizeStart + sizeVar * Random(sizeStart, sizeEnd);
		particles[numLiveParticles].angle0 = (1.0f - angleVar) * angleStart + angleVar * Random(angleStart, angleEnd);
		particles[numLiveParticles].color0 = colorStart;
		numLiveParticles++;
	}

	for(int i = 0; i < numLiveParticles; i++)
	{

		if(particles[i].age + deltaTime > particles[i].lifetime)
		{
			particles[i] = particles[numLiveParticles-1];
			numLiveParticles--;
		}


		particles[i].age += deltaTime;
		particles[i].position += deltaTime * particles[i].velocity;
		particles[i].velocity += deltaTime * particles[i].acceleration;
	}
}

void ParticleSystemRenderComponent::Draw()
{
	Transform *transform = &GetOwner()->transform;
	Vector2 p = transform->GetPosition();
	float   r = transform->GetRotation();

	for(int i = 0; i < numLiveParticles; i++)
	{
		float t = particles[i].age / particles[i].lifetime;
		float size = particles[i].size0 + t * (sizeEnd - sizeStart);
		float angle = particles[i].angle0 + t * (angleEnd - angleStart);
		Color4f color;
		color.r = particles[i].color0.r + t * (colorEnd.r - colorStart.r);
		color.g = particles[i].color0.g + t * (colorEnd.g - colorStart.g);
		color.b = particles[i].color0.b + t * (colorEnd.b - colorStart.b);
		color.a = particles[i].color0.a + t * (colorEnd.a - colorStart.a);
		Vector2 position = p + Matrix2x2(r) * particles[i].position; 
		Renderer::DrawTexturedQuad(texture, position, size, size, angle, Vector2(0,0), false, false, color);
	}
}