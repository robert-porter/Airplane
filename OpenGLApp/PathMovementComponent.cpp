#include "PathMovementComponent.h"
#include "Entity.h"
#include "Vector2.h"
#include "Transform.h"

PathMovementComponent::PathMovementComponent(Entity *owner, float linearSpeed) :  MovementComponent(owner)
{
	name = "StraightPathMovement";
	speed = linearSpeed;
	time = 0.0f;


	const int n = 12;
	Vector2 points[n];

	float xmin = -3;
	float xmax = 3;
	float x = xmin;
	for(int i = 0; i < n; i++)
	{
		x += (xmax - xmin) / float(n);
		float y = (x-2)*(x+2);
		points[i].Set(x,y);
	}
	path = new Path(points, n, false);
}

/*
PathMovementComponent::PathMovementComponent(TiXmlElement *xmlElement)
{
	name = "StraightPathMovement";
	xmlElement->QueryFloatAttribute("speed", &speed);
	this->xmlElement = xmlElement;
	initialPosition = Vector2(0,0);
	position = Vector2(0,0);
	time = 0.0f;
	direction = GetFacing();
	const int n = 12;
	Vector2 points[n];

	float xmin = -4;
	float xmax = 4;
	float x = xmin;
	for(int i = 0; i < n; i++)
	{
		float y = (x-2)*(x+2);
		x += (xmax - xmin) / float(n);
	}
	path = new Path(points, n, false);
}
*/

PathMovementComponent::~PathMovementComponent()
{
	if(path)
		delete path;
}

void PathMovementComponent::Update(float deltaTime)
{
	time+=deltaTime;
	path->Advance(speed * deltaTime);
	GetOwner()->transform.SetPosition( path->GetPosition() );
	GetOwner()->transform.SetRotation( path->GetRotation() );
}