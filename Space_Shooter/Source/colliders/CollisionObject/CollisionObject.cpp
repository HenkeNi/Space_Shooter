#include "pch.h"
#include "CollisionObject.h"
#include "Dispatcher.h"
#include "Entity.h"


CollisionObject::CollisionObject(eCollisionLayer aLayer) 
	: m_collisionLayer { aLayer }, m_owner{ nullptr }
{
}

CollisionObject::~CollisionObject()
{
	Dispatcher::GetInstance().SendEvent(Event{ eEvent::ColliderDestroyed, this });
}

void CollisionObject::DrawDebug(sf::RenderTarget& aTarget) 
{
}

const CU::Vector2<float>& CollisionObject::GetPosition()	const
{
	return m_position;
}

eCollisionLayer	CollisionObject::GetCollisionLayer()		const 
{ 
	return m_collisionLayer; 
}

Entity* CollisionObject::GetOwner()							const
{
	return m_owner;
}

bool CollisionObject::CollidesWithLayer(eCollisionLayer aLayer) const
{
	return m_layersToCollideWith.find(aLayer) != m_layersToCollideWith.end();
}

bool CollisionObject::AddCollisionLayer(eCollisionLayer aLayer)
{
	if (m_layersToCollideWith.find(aLayer) != m_layersToCollideWith.end()) { return false; }
	
	m_layersToCollideWith.insert(aLayer);
	return true;
}

void CollisionObject::SetPosition(const CU::Vector2<float>& aPosition)
{
	m_position = aPosition;
}

void CollisionObject::SetOwner(Entity* aOwner)
{
	m_owner = aOwner;
}
