#include "Airplane.h"
#include "Bullet.h"
#include "Gun.h"

Airplane::Airplane(void)
{
	type = ET_AIRPLANE;
	health = 0.0f;
	maxHealth = 0.0f;
	lives = 0;
}

Airplane::~Airplane(void)
{
}

void Airplane::Touch(Airplane *airplane)
{

}
void Airplane::Touch(Bullet *bullet)
{
	health -= bullet->damage;
	if(health < 0)
		lives--;
	if(lives < 0)
		Invalidate();
}
void Airplane::Touch(Powerup *powerup)
{

}

void Airplane::Fire(unsigned int gun)
{
	assert(gun < guns.size());
	Gun *g = guns[gun];
	g->AttemptToFire();
}