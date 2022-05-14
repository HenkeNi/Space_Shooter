#include "pch.h"
#include "PickupSpawner.h"
#include "PickupFactory.h"
#include "eEvent.h"
#include "Dispatcher.h"
#include "Vector.hpp"
#include "UtilityFunctions.hpp"
#include "Pickup.h"


PickupSpawner::PickupSpawner(PickupFactory& aPickupFactory)
	: m_pickupFactory{ aPickupFactory }
{
	Dispatcher::GetInstance().Subscribe(eEvent::EnemyDeath, this);
}

PickupSpawner::~PickupSpawner()
{
	Dispatcher::GetInstance().Unsubscribe(eEvent::EnemyDeath, this);
}

void PickupSpawner::Recieve(const Event& aEvent)
{
	switch (aEvent.GetEventType())
	{
	case eEvent::EnemyDeath:
		SpawnRandomPickup(std::any_cast<CU::Vector2<float>>(std::get<std::any>(aEvent.GetData())));
		break;
	}
}

void PickupSpawner::SpawnRandomPickup(const CU::Vector2<float>& aPosition)
{
	if (ShouldSpawn())
	{
		Pickup* pickup = m_pickupFactory.CreatePickup(CU::GetRandomNumber<int>(0, 2)); 
		pickup->SetPosition(aPosition);

	}
}

bool PickupSpawner::ShouldSpawn() const
{
	return CU::GetRandomNumber(1, 10) % 5 == 0;
}