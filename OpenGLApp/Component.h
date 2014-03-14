#pragma once

#include "stdincludes.h"

class Entity;


class Component
{
public:
	Component(Entity *o) { owner = o; }
	virtual ~Component(void) { }

	const std::string &GetName() { return name; }
	const std::string &GetFamilyName() const { return familyName; }

	void SetOwner(Entity *  e) { owner = e; }
	const Entity *  GetOwner() const { return owner; }
	Entity *  GetOwner() { return owner; }

protected:
	Entity * owner;
	std::string name;
	std::string familyName;
};
