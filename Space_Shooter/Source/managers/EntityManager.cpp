#include "pch.h"
#include "EntityManager.h"
#include "Boss.h"
#include "Bullet.h"
#include "Dispatcher.h"
#include "Enemy.h"
#include "Player.h"
#include "Pickup.h"



EntityManager::EntityManager(sf::RenderWindow& aWindow)
	: m_window{ aWindow }
{
	m_entities.reserve(200);
}

EntityManager::~EntityManager()
{
	CancelSubscriptions();
	Clear();
}

void EntityManager::Recieve(const Event& aEvent)
{
	switch (aEvent.GetEventType())
	{
	case eEvent::BossCreated: // Just EntityCreated??
		AddEntity(std::any_cast<Boss*>(std::get<std::any>(aEvent.GetData())));
		break;
	case eEvent::BulletCreated:
		AddEntity(std::any_cast<Bullet*>(std::get<std::any>(aEvent.GetData())));
		break;
	case eEvent::EnemyCreated:
		AddEntity(std::any_cast<Enemy*>(std::get<std::any>(aEvent.GetData()))); 
		break;
	case eEvent::PlayerCreated:
		AddEntity(std::any_cast<Player*>(std::get<std::any>(aEvent.GetData())));
		break;
	case eEvent::PickupCreated:
   		AddEntity(std::any_cast<Pickup*>(std::get<std::any>(aEvent.GetData())));
		break;
	case eEvent::PlayerDeath: // TODO:: HAVE IT HERE?? OR make sometinh listen to player death and call it manually
		Clear();
		break;
		// Level end/start -> empty entities??

		// factories or spawners sends post ?? that enemy or something was created...
	}
}

void EntityManager::Update(float aDeltaTime)
{
	UpdateEntities(aDeltaTime);
}

void EntityManager::Render(sf::RenderTarget& aTarget) const
{
	for (auto& entity : m_entities)
		entity->Render(aTarget);
}

void EntityManager::AddEntity(Entity* aEntity)
{
	// assert entities doesn't contain already...
	m_entities.push_back(std::move(aEntity));
}

void EntityManager::RemoveEntity(const unsigned int aID)
{
}

void EntityManager::Clear()
{
	for (auto entity : m_entities)
		delete entity; // FIX CRASCH!

	m_entities.clear();
}

void EntityManager::Init()
{
	SetupSubscriptions();
}

void EntityManager::SetupSubscriptions()
{
	Dispatcher::GetInstance().Subscribe(eEvent::BossCreated, this);
	Dispatcher::GetInstance().Subscribe(eEvent::BulletCreated, this);
	Dispatcher::GetInstance().Subscribe(eEvent::EnemyCreated, this);
	Dispatcher::GetInstance().Subscribe(eEvent::PlayerCreated, this);
	Dispatcher::GetInstance().Subscribe(eEvent::PickupCreated, this);
	Dispatcher::GetInstance().Subscribe(eEvent::PlayerDeath, this);
}

void EntityManager::CancelSubscriptions()
{
	Dispatcher::GetInstance().Unsubscribe(eEvent::BossCreated, this);
	Dispatcher::GetInstance().Unsubscribe(eEvent::BulletCreated, this);
	Dispatcher::GetInstance().Unsubscribe(eEvent::EnemyCreated, this);
	Dispatcher::GetInstance().Unsubscribe(eEvent::PlayerCreated, this);
	Dispatcher::GetInstance().Unsubscribe(eEvent::PickupCreated, this);
}

void EntityManager::UpdateEntities(float aDeltaTime)
{
	for (int i = 0; i < m_entities.size(); ++i)
	{
		if (m_entities[i]->IsMarkedForRemoval() || IsOutOfBounds(*m_entities[i]))
		{
			delete m_entities[i];
			m_entities.erase(m_entities.begin() + i);
		}
		else
		{
			m_entities[i]->Update(aDeltaTime);
		}
	}
}

bool EntityManager::IsOutOfBounds(Entity& aEntity)
{
	return aEntity.IsOutOfBounds({ m_window.getSize().x, m_window.getSize().y });
}
