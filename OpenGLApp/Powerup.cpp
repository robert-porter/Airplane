#include "Powerup.h"
#include "Airplane.h"
#include "Gun.h"

Powerup::Powerup() 
{
	type = ET_POWERUP;
	name = "Powerup";

	bullet = false;
	multi = false;
	spread = false;
	rapid = false;
}

Powerup::~Powerup(void)
{
}

void Powerup::Touch(Airplane *airplane)
{
	Gun *gun = airplane->guns[0];

	gun->ToggleBulletType();

	if(bullet)
		gun->SetBulletType(bulletType);
	else if(multi)
		gun->UpgradeMultiShot();
	else if(spread)
		gun->UpgradeSpreadShot();
	else if(rapid)
		gun->UpgradeRapidShot();

	Invalidate();
}


void Powerup::SetRandom() {
	int r = rand() % (BT_NUM_TYPES + 3);
	if(r < BT_NUM_TYPES)
	{
		bullet = true;
		bulletType = (BULLET_TYPE)(r);
	}
	else if(r == BT_NUM_TYPES)
		rapid = true;
	else if(r == BT_NUM_TYPES + 1)
		spread = true;
	else if(r == BT_NUM_TYPES + 2)
		multi = true;
}