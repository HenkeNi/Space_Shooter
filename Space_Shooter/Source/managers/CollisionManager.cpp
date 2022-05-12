#include "pch.h"
#include "CollisionManager.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Dispatcher.h"
#include "Entity.h"
#include "eEvent.h"


CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
	Dispatcher::GetInstance().Unsubscribe(eEvent::BoxColliderCreated,		this);
	Dispatcher::GetInstance().Unsubscribe(eEvent::CircleColliderCreated,    this);
	Dispatcher::GetInstance().Unsubscribe(eEvent::ColliderDestroyed,		this);
}

void CollisionManager::Init()
{
	Dispatcher::GetInstance().Subscribe(eEvent::BoxColliderCreated,		this);
	Dispatcher::GetInstance().Subscribe(eEvent::CircleColliderCreated,	this);
	Dispatcher::GetInstance().Subscribe(eEvent::ColliderDestroyed,		this);
}

void CollisionManager::Recieve(const Event& aEvent)
{
	switch (aEvent.GetEventType())
	{
	case eEvent::BoxColliderCreated:
		AddCollider(std::any_cast<BoxCollider*>(std::get<std::any>(aEvent.GetData())));
		break;
	case eEvent::CircleColliderCreated: // TODO: COMBINE?? - didn't seem to work!
		AddCollider(std::any_cast<CircleCollider*>(std::get<std::any>(aEvent.GetData())));
		break;
	case eEvent::ColliderDestroyed:
		RemoveCollider(std::any_cast<CollisionObject*>(std::get<std::any>(aEvent.GetData())));
		break;
	}
}

void CollisionManager::Update(float aDeltaTime)
{
	CheckCollisions();
}

void CollisionManager::AddCollider(CollisionObject* aObject)
{
	assert(std::find(m_collisionObjects.begin(), m_collisionObjects.end(), aObject) == m_collisionObjects.end());
	m_collisionObjects.push_back(aObject);
}

void CollisionManager::RemoveCollider(CollisionObject* aObject)
{
	assert(std::find(m_collisionObjects.begin(), m_collisionObjects.end(), aObject) != m_collisionObjects.end());
	m_collisionObjects.erase(std::remove(m_collisionObjects.begin(), m_collisionObjects.end(), aObject), m_collisionObjects.end());
}

void CollisionManager::CheckCollisions()
{
	for (int i = 0; i < m_collisionObjects.size(); ++i)
	{
		for (int j = i + 1; j < m_collisionObjects.size(); ++j)
		{
			if (!m_collisionObjects[i]->CollidesWithLayer(m_collisionObjects[j]->GetCollisionLayer())) { continue; }
			if (m_collisionObjects[i]->IsColliding(*m_collisionObjects[j]))
			{
				m_collisionObjects[i]->GetOwner()->OnCollision(*m_collisionObjects[j]->GetOwner());
				m_collisionObjects[j]->GetOwner()->OnCollision(*m_collisionObjects[i]->GetOwner());
			}
		}
	}
}