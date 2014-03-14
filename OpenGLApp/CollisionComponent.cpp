#include "stdincludes.h"

#include "CollisionComponent.h"
#include "Renderer.h"
#include "Entity.h"

CollisionComponent::CollisionComponent(Entity *owner) : Component(owner)
{
	familyName = "Collision";
	name = "Collision";
}


CollisionCircle::CollisionCircle(Entity *owner, float r) : CollisionComponent(owner)
{
	familyName = "Collision";
	name = "CircleCollision";
	radius = r;
}

bool CollisionCircle::IntersectShape(const CollisionComponent *s) const
{
	//Vector2 P0 = GetOwner()->transform.GetPosition();
	//float   r0 = GetOwner()->transform.GetRotation();
	//Vector2 P1 = s->GetOwner()->transform.GetPosition();
	//float   r1 = s->GetOwner()->transform.GetRotation();
	return s->IntersectCircle(this);
}

bool CollisionCircle::IntersectCircle(const CollisionCircle *s) const
{
	Vector2 P0 = GetOwner()->transform.GetPosition();
	float   r0 = GetOwner()->transform.GetRotation();
	float   s0 = GetOwner()->transform.GetScale();
	Vector2 P1 = s->GetOwner()->transform.GetPosition();
	float   r1 = s->GetOwner()->transform.GetRotation();
	float   s1 = s->GetOwner()->transform.GetScale();
	float   radius0 = this->radius * s0;
	float   radius1 = s->radius * s1;
	return IntersectCircleCircle(P0, radius0, P1, radius1);
}
bool CollisionCircle::IntersectCapsule(const CollisionCapsule *s) const
{
	Vector2 P0 = GetOwner()->transform.GetPosition();
	float   r0 = GetOwner()->transform.GetRotation();
	float   s0 = GetOwner()->transform.GetScale();
	float   radius0 = this->radius * s0;

	Vector2 P1 = s->GetOwner()->transform.GetPosition();
	float   r1 = s->GetOwner()->transform.GetRotation();
	float   s1 = s->GetOwner()->transform.GetScale();
	float   radius1 = s->radius * s1;
	Vector2 A = s->p0;
	Vector2 B = s->p1;
	Matrix2x2 rot(r1);
	A = rot*A;
	B = rot*B;
	A = s1 * A;
	B = s1 * B;

	return IntersectCircleCapsule(P0, radius0, A + P1, B + P1, radius1);
}

void CollisionCircle::Draw() const 
{
	Vector2 pos = GetOwner()->transform.GetPosition();
	float   rad = this->radius;
	Renderer::DrawCircle(pos, rad * GetOwner()->transform.GetScale());
}

CollisionCapsule::CollisionCapsule(Entity *owner, const Vector2& P0, const Vector2 &P1, float rad) : CollisionComponent(owner)
{
	radius = rad;
	p0 = P0;
	p1 = P1;
}


bool CollisionCapsule::IntersectShape(const CollisionComponent *s)const
{
	return s->IntersectCapsule(this);
}

bool CollisionCapsule::IntersectCircle(const CollisionCircle *s)const
{
	Vector2 P0 = s->GetOwner()->transform.GetPosition();
	float   r0 = s->GetOwner()->transform.GetRotation();
	float   s0 = s->GetOwner()->transform.GetScale();
	float   radius0 = s->radius * s0;

	Vector2 P1 = GetOwner()->transform.GetPosition();
	float   r1 = GetOwner()->transform.GetRotation();
	float   s1 = GetOwner()->transform.GetScale();
	float   radius1 = radius * s1;
	Vector2 A = p0;
	Vector2 B = p1;
	Matrix2x2 rot(r1);
	A = rot*A;
	B = rot*B;
	A = s1 * A;
	B = s1 * B;

	return IntersectCircleCapsule(P0, radius0, A + P1, B + P1, radius1);
}

bool CollisionCapsule::IntersectCapsule(const CollisionCapsule *s)const
{
//	assert(false);
	return false;
}

void CollisionCapsule::Draw() const
{
	Vector2 pos = GetOwner()->transform.GetPosition();
	float   rot = GetOwner()->transform.GetRotation();
	float   scale = GetOwner()->transform.GetScale();
	float   rad = radius * scale;
	Vector2 A = scale * p0;
	Vector2 B = scale * p1;
	Renderer::DrawCapsule(pos, rot, A, B, rad);
}


CollisionOutOfBounds::CollisionOutOfBounds(Entity *owner, float r) : CollisionCircle(owner, r)
{
	familyName = "Collision";
	name = "OutOfBoundsCollision";
}

bool CollisionOutOfBounds::IntersectShape(const CollisionComponent *s)const
{
	return !s->IntersectCircle(this);
}

bool CollisionOutOfBounds::IntersectCircle(const CollisionCircle *s)const
{
	Vector2 P0 = GetOwner()->transform.GetPosition();
	float   r0 = GetOwner()->transform.GetRotation();
	float   s0 = GetOwner()->transform.GetScale();
	Vector2 P1 = s->GetOwner()->transform.GetPosition();
	float   r1 = s->GetOwner()->transform.GetRotation();
	float   s1 = s->GetOwner()->transform.GetScale();
	float   radius0 = this->radius * s0;
	float   radius1 = s->radius * s1;
	return !IntersectCircleCircle(P0, radius0, P1, radius1);
}
bool CollisionOutOfBounds::IntersectCapsule(const CollisionCapsule *s)const
{

	Vector2 P0 = GetOwner()->transform.GetPosition();
	float   r0 = GetOwner()->transform.GetRotation();
	float   s0 = GetOwner()->transform.GetScale();
	float   radius0 = radius * s0;

	Vector2 P1 = s->GetOwner()->transform.GetPosition();
	float   r1 = s->GetOwner()->transform.GetRotation();
	float   s1 = s->GetOwner()->transform.GetScale();
	float   radius1 = s->radius * s1;
	Vector2 A = s->p0;
	Vector2 B = s->p1;
	Matrix2x2 rot(r1);
	A = rot*A;
	B = rot*B;
	A = s1 * A;
	B = s1 * B;
	return !IntersectCircleCapsule(P0, radius0, A + P1, B + P1, radius1);

}

void CollisionOutOfBounds::Draw() const
{
	Renderer::DrawCircle( GetOwner()->transform.GetPosition(), radius * GetOwner()->transform.GetScale());
}
