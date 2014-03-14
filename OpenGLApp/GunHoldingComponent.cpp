#include "GunHoldingComponent.h"
#include <cassert>
#include "Entity.h"
#include "GunComponent.h"
#include "GunHoldingComponent.h"

GunHoldingComponent::GunHoldingComponent()
{
	familyName = "GunHolding";
	name = "GunHolding";
}

GunHoldingComponent::~GunHoldingComponent(void)
{
}

void GunHoldingComponent::Fire(unsigned int gun)
{
	assert(gun < guns.size());
	GunComponent *gunComponent = (GunComponent *) guns[gun]->GetComponent("Gun");
	gunComponent->AttemptToFire();
}

