#include "pch.h"
#include "Weapon.h"
#include "Event.h"
#include "Dispatcher.h"
#include "Bullet.h"


Weapon::Weapon(WeaponData& someData, bool isPlayers)
	: m_weaponData{ someData }, m_projectileSpeedMultiplier{ 1 }, m_isPlayers{ isPlayers }
{
}

Weapon::~Weapon()
{
}

void Weapon::Shoot(const CU::Vector2<float>& aPosition)
{
	if (IsReadyToFire())
	{
		Dispatcher::GetInstance().SendEvent(Event{ m_isPlayers ? eEvent::PlayerFire : eEvent::EnemyFire, std::tuple<CU::Vector2<float>, CU::Vector2<float>>(aPosition, {0.f, m_isPlayers ? -1.f : 1.f}) });
		Reload();
	}
}

void Weapon::SetProjectileSpeedMultiplier(int aMultiplier)
{
	assert(aMultiplier > 0);
	m_projectileSpeedMultiplier = aMultiplier;
}

void Weapon::Reload()
{
	m_nextShotClock.restart();
}

bool Weapon::IsReadyToFire() const
{
	return m_nextShotClock.getElapsedTime().asSeconds() > m_weaponData.m_nextShotDelay;
}