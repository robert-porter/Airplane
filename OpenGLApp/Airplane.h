#pragma once
#include "Entity.h"

class Airplane : public Entity
{
public:
	Airplane(void);
	~Airplane(void);

	void Touch(Airplane *airplane);
	void Touch(Bullet *bullet);
	void Touch(Powerup *powerup);

	void AddGun(Gun * g) { guns.push_back(g); }
	void Fire(unsigned int gun);

	//void Kill();

	std::vector<Gun *> guns;

	float health;
	float maxHealth;
	int   lives;
};
