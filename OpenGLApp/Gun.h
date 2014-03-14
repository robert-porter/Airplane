#pragma once
#include "entity.h"

class Gun :
	public Entity
{
public:
	Gun(int);
	~Gun(void);

	void SetBulletType(BULLET_TYPE);
	void Update(float deltaTime);
	void AttemptToFire() { fireAttempted = true; }
	void ToggleBulletType() { 
		bulletType = (BULLET_TYPE)((int(bulletType) + 1) % int(BT_NUM_TYPES)); 
		SetBulletType(bulletType);
	}

	void ToggleMultiShot() { 
		multiShot++;
		if(multiShot > 3)
			multiShot = 1;
	}
	void ToggleRapidShot() { 
		rapidShot++;
		if(rapidShot > 3)
			rapidShot = 1;
	}
	void ToggleSpreadShot() { 
		spreadShot++;
		if(spreadShot > 3)
			spreadShot = 1;
	}
	void UpgradeMultiShot() { 
		multiShot++;
		if(multiShot > 3)
			multiShot = 3;
	}
	void UpgradeRapidShot() { 
		rapidShot++;
		if(rapidShot > 3)
			rapidShot = 3;
	}
	void UpgradeSpreadShot() { 
		spreadShot++;
		if(spreadShot > 3)
			spreadShot = 3;
	}
private:
	void FireBullets(const Vector2 &pos, float angle);
	BULLET_TYPE         bulletType;

	int					multiShot;
	int					spreadShot;
	int					rapidShot;

	bool				fireAttempted;
	float				timeAccum;
	float				fireDelay;
	float				fireDelayMultiplier;
};
