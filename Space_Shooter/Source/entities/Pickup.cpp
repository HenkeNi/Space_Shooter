#include "pch.h"
#include "Pickup.h"
#include "Dispatcher.h"

#define MOVEMENT_SPEED 150.0


Pickup::Pickup(PickupData& someData)
	: Entity{ *someData.m_texture }, m_pickupData{ someData }, m_velocity{ 0.f, 1.f }, m_isCollected{ false }
{
	Dispatcher::GetInstance().SendEvent(Event{ eEvent::PickupCreated, this }); 
}

Pickup::~Pickup()
{
}

void Pickup::Recieve(const Event& aEvent)
{
}

void Pickup::OnCollision(Entity& aEntity)
{
	m_isCollected = true;
}

void Pickup::Update(float aDeltaTime)
{
	UpdateMovement(aDeltaTime);
	UpdateCollider();
}

bool Pickup::IsMarkedForRemoval() const
{
	return m_isCollected;
}

Effect* Pickup::GetEffect() const
{
	return m_pickupData.m_effect;
}

void Pickup::UpdateMovement(float aDeltaTime)
{
	m_position += m_velocity * (float)MOVEMENT_SPEED * aDeltaTime;
	m_sprite.setPosition({ m_position.x, m_position.y });
}