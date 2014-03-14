#pragma once
#include "entity.h"

class Bullet : public Entity
{
public:
	Bullet(void);
	~Bullet(void);

	void Touch(Airplane *airplane);

	float damage;
};
