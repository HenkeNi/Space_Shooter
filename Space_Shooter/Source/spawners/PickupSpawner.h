#pragma once
#include "Subscriber.h"
#include "Vector.hpp"

namespace CU = CommonUtilities;


class PickupFactory;

class PickupSpawner : public Subscriber
{
public:
	PickupSpawner(PickupFactory& aPickupFactory);
	~PickupSpawner();

	virtual void	Recieve(const Event& aEvent) override;

private:
	void			SpawnRandomPickup(const CU::Vector2<float>& aPosition);
	bool			ShouldSpawn() const;

	/* - Members - */
	PickupFactory&	m_pickupFactory;
};

