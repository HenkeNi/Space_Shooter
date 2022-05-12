#include "pch.h"
#include "Bullet.h"
#include "BulletSpawner.h"
#include "BulletFactory.h"
#include "Dispatcher.h"


BulletSpawner::BulletSpawner(BulletFactory& aFactory/*, EntityManager& anEntityManager*/)
	: m_bulletFactory{ aFactory }/*, m_entityManager{ anEntityManager }*/
{
	Dispatcher::GetInstance().Subscribe(eEvent::PlayerFire, this);
	Dispatcher::GetInstance().Subscribe(eEvent::EnemyFire, this);
}

BulletSpawner::~BulletSpawner()
{
	Dispatcher::GetInstance().Unsubscribe(eEvent::PlayerFire, this);
	Dispatcher::GetInstance().Unsubscribe(eEvent::EnemyFire, this);
}

void BulletSpawner::Recieve(const Event& aEvent)
{
	switch (aEvent.GetEventType())
	{
	case eEvent::PlayerFire:
		SpawnPlayerBullet(std::any_cast<std::tuple<CU::Vector2<float>, CU::Vector2<float>>>(std::get<std::any>(aEvent.GetData())));
		break;
	case eEvent::EnemyFire:
		SpawnEnemyBullet(std::any_cast<std::tuple<CU::Vector2<float>, CU::Vector2<float>>>(std::get<std::any>(aEvent.GetData())));
		break;
	}
}

void BulletSpawner::SpawnPlayerBullet(const std::tuple<CU::Vector2<float>, CU::Vector2<float>> someBulletData)
{
	SpawnPlayerBullet(std::get<0>(someBulletData), std::get<1>(someBulletData));
}

void BulletSpawner::SpawnPlayerBullet(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aVelocity)
{
	Bullet* bullet = m_bulletFactory.CreatePlayerBullet(0); // TODO: accpet bullet type? - or use BulletId in Weapons.Json... 
	bullet->SetPosition(aPosition);
	bullet->SetVelocity(aVelocity);

	//Dispatcher::GetInstance().SendEvent(Event{ eEvent::BulletCreated, bullet });

	/*auto bullet = m_bulletFactory.CreateBullet(0);
	bullet->SetPosition(aPosition);
	bullet->SetVelocity(aVelocity);*/

	//m_entityManager.AddEntity(std::move(bullet));
}

void BulletSpawner::SpawnEnemyBullet(const std::tuple<CU::Vector2<float>, CU::Vector2<float>> someBulletData)
{
	SpawnEnemyBullet(std::get<0>(someBulletData), std::get<1>(someBulletData));
}

void BulletSpawner::SpawnEnemyBullet(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aVelocity)
{
	Bullet* bullet = m_bulletFactory.CreateEnemyBullet(3);
	bullet->SetPosition(aPosition);
	bullet->SetVelocity(aVelocity);

	//Dispatcher::GetInstance().SendEvent(Event{ eEvent::BulletCreated, bullet });
}