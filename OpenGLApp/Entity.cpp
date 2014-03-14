#include "stdincludes.h"
#include "Entity.h"



Entity::Entity(void)
{
	type = ET_NONE;
	name = "Entity";
	team = 0;
	valid = true;
	visual = 0;
	shape = 0;
	movement = 0;
	think = 0;
}

Entity::~Entity(void)
{
	if(visual)
		delete visual;
	if(think)
		delete think;
	if(movement)
		delete movement;
	if(shape)
		delete shape;
}

///void Entity::AddRef() 
//{ 
//	refCount++;
//}

//void Entity::RemRef() 
//{ 
//	refCount--; 
//}

//int Entity::GetRefCount() const 
//{ 
//	return refCount;
//}

void Entity::AddChild(Entity * child) 
{ 
	if ( child != 0 ) 
		children.push_back(child); 
}

bool Entity::IsValid() const
{ 
	return valid; 
}

void Entity::Invalidate() 
{
	valid = false;
	for ( unsigned int i = 0; i < children.size(); i++ )
		children[i]->Invalidate();
}

const std::string & Entity::GetName() const 
{ 
	return name; 
}

void Entity::SetName(const std::string &n) 
{ 
	name = n; 
}










