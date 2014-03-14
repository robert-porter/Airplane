#pragma once

#include "stdincludes.h"
#include "CollisionBase.h"

#include "Vector2.h"
#include "Matrix2x2.h"
#include "Component.h"
#include "CollisionBase.h"


class CollisionCircle;
class CollisionCapsule;
class CollisionOutOfBounds;

class CollisionComponent : public Component
{
public:
					CollisionComponent(Entity *owner);
	virtual			~CollisionComponent() { }
	virtual bool	IntersectShape(const CollisionComponent *s) const = 0;
	virtual bool	IntersectCircle(const CollisionCircle *s) const = 0;
	virtual bool	IntersectCapsule(const CollisionCapsule *s) const = 0;
	virtual void	Draw() const = 0; 
private:
	friend class CollisionCircle;
    friend class CollisionCapsule;
	friend class CollisionOutOfBounds;
};

class CollisionCircle : public CollisionComponent
{
public:
					CollisionCircle(Entity *owner, float r);
	virtual bool	IntersectShape(const CollisionComponent *s) const;
	virtual bool	IntersectCircle(const CollisionCircle *s) const;
	virtual bool	IntersectCapsule(const CollisionCapsule*s) const;
	virtual void	Draw() const; 
protected:
	float radius;

    friend class CollisionCapsule;
	friend class CollisionOutOfBounds;
};

class CollisionCapsule : public CollisionComponent 
{
public:
					CollisionCapsule(Entity *owner, const Vector2& P0, const Vector2 &P1, float rad);
	bool			IntersectShape(const CollisionComponent *s) const;
	bool			IntersectCircle(const CollisionCircle *s) const;
	bool			IntersectCapsule(const CollisionCapsule *s) const;
	virtual void	Draw() const; 
private:
	Vector2 p0, p1;
	float radius;
	friend class CollisionCircle;
	friend class CollisionOutOfBounds;
};

class CollisionOutOfBounds : public CollisionCircle
{
public:
					CollisionOutOfBounds(Entity *owner, float r);
					~CollisionOutOfBounds() {  }
	bool			IntersectShape(const CollisionComponent *s) const;
	bool			IntersectCircle(const CollisionCircle *s) const;
	bool			IntersectCapsule(const CollisionCapsule*s) const;
	virtual void	Draw() const; 
private:
	friend class CollisionCircle;
    friend class CollisionCapsule;
};
