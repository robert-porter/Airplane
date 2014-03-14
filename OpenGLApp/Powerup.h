#pragma once
#include "entity.h"

class Powerup : public Entity
{
public:
	Powerup(void);
	~Powerup(void);

	void Touch(Airplane *airplane);

	void SetBullet(enum BULLET_TYPE bt) { bullet = true; bulletType = bt; }
	void SetRapid() { rapid = true; } 
	void SetSpread() { spread = true; }
	void SetMulti() { multi = true; }

	void SetRandom();

private:

	BULLET_TYPE bulletType;
	bool bullet;
	bool rapid;
	bool spread;
	bool multi;
};
