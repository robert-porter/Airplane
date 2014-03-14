#include "Gun.h"
#include "EntityFactory.h"

Gun::Gun(int team)
{
	name = "Gun";
	type = ET_GUN;
	this->team = team;
	fireAttempted = false;
	timeAccum = 0.0f;
	fireDelay = 0.0f;
	SetBulletType(BT_LASER);
	fireDelayMultiplier = 1.0f;
	multiShot = 1;
	rapidShot = 1;
	spreadShot = 1;
}

Gun::~Gun(void)
{

}
void Gun::SetBulletType(BULLET_TYPE bt)
{
	bulletType = bt;
	fireDelay = EntityFactory::GetFireDelay(bt);
}


void Gun::Update(float deltaTime)
{
	timeAccum += deltaTime;

	if(rapidShot == 1)
		fireDelayMultiplier = 1.0f;
	if(rapidShot == 2)
		fireDelayMultiplier = 1.0f / 3.0f;
	if(rapidShot == 3)
		fireDelayMultiplier = 1.0f / 3.0f;

	if ( fireAttempted  && timeAccum >= fireDelayMultiplier * fireDelay )
	{
		if(spreadShot == 1)
			FireBullets(transform.GetPosition(), transform.GetRotation());
		if(spreadShot == 2)
		{
	
			float ang = 8.0f/(2.0f * PI);
			FireBullets(transform.GetPosition(), transform.GetRotation() + ang);
			FireBullets(transform.GetPosition(), transform.GetRotation());
			FireBullets(transform.GetPosition(), transform.GetRotation() -ang);
		}
		if(spreadShot == 3)
		{
			float ang = 8.0f/(2.0f * PI);
			FireBullets(transform.GetPosition(), transform.GetRotation() + ang);
			FireBullets(transform.GetPosition(), transform.GetRotation() + ang/2.0f);
			FireBullets(transform.GetPosition(), transform.GetRotation());
			FireBullets(transform.GetPosition(), transform.GetRotation() - ang/2.0f);
			FireBullets(transform.GetPosition(), transform.GetRotation() -ang);
		}

		timeAccum = 0.0f;
	}

	fireAttempted = false;
}

void Gun::FireBullets(const Vector2 &pos, float angle)
{
	if(multiShot == 1)
		EntityFactory::CreateBullet(bulletType, pos, angle, team);
	else if(multiShot == 2)
	{
		Vector2 right = Vector2(cosf(angle), sinf(angle));
		float offset = 0.1;
		EntityFactory::CreateBullet(bulletType, pos + offset* right, angle, team);
		EntityFactory::CreateBullet(bulletType, pos - offset* right, angle, team);
	}
	else if(multiShot == 3)
	{
		Vector2 right = Vector2(cosf(angle), sinf(angle));
		float offset = 0.1;
		EntityFactory::CreateBullet(bulletType, pos + offset* right, angle, team);
		EntityFactory::CreateBullet(bulletType, pos - offset* right, angle, team);
		EntityFactory::CreateBullet(bulletType, pos, angle, team);
	}
}