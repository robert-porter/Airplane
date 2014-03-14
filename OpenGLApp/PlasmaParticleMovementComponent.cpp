#include "PlasmaParticleMovementComponent.h"
#include "Entity.h"
#include "MathUtils.h"

PlasmaParticleMovementComponent::PlasmaParticleMovementComponent(Entity *owner, float linearSpeed, float amp, float freq) : MovementComponent(owner)
{
	speed = linearSpeed;
	time = 0;
	amplitude = amp;
	k = freq;
	w0 = Random(0.0f, 2.0f*PI);
}

PlasmaParticleMovementComponent::~PlasmaParticleMovementComponent(void)
{
}

void PlasmaParticleMovementComponent::Update(float deltaTime)
{
	float deltaSin = sinf(k*(time+deltaTime)+w0)-sinf(k*time+w0);
	time += deltaTime;
	Vector2 deflection = amplitude * deltaSin * GetOwner()->transform.GetRight();
	GetOwner()->transform.Translate( speed * deltaTime * GetOwner()->transform.GetUp() + deflection );
}