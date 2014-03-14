#include "Bullet.h"

Bullet::Bullet(void)
{
	type = ET_BULLET;
}

Bullet::~Bullet(void)
{
}

void Bullet::Touch(Airplane *airplane)
{
	Invalidate();
}