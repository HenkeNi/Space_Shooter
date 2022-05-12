#pragma once
#include "ePickupType.h"
#include "PickupData.h"
#include "SharedContext.h"


class ColliderFactory;
class Effect;
class Pickup;

class PickupFactory
{
public:
	using PickupData_t = std::array<PickupData, static_cast<int>(ePickupType::Count)>;

	PickupFactory(SharedContext aSharedContext, ColliderFactory& aColliderFactory);
	~PickupFactory();

	void					Init();
	Pickup*					CreatePickup(int aType);

private:
	/* - Methods - */
	void					InitEffects();
	void					LoadPickupData();

	/* - Members - */
	PickupData_t			m_pickupData;
	std::array<Effect*, 3>	m_effects;
	SharedContext			m_sharedContext;
	ColliderFactory&		m_colliderFactory;
};