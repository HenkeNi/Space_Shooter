#pragma once
#include "WeaponData.h"
#include "Vector.hpp"


namespace CU = CommonUtilities;

class Weapon
{
public:
	Weapon(WeaponData& someData, bool isPlayers);
	~Weapon();
		
	void			Shoot(const CU::Vector2<float>& aPosition);
	void			SetProjectileSpeedMultiplier(int aMultiplier);

private:
	/* - Methods - */
	void			Reload();
	bool			IsReadyToFire() const;

	/* - Members - */
	WeaponData&		m_weaponData; 
	sf::Clock		m_nextShotClock;
	int				m_projectileSpeedMultiplier;
	bool			m_isPlayers;

	//std::vector<CU::Vector2<float>> m_bulletSpawnPoints;

	//sf::Vector2f m_spawnOffset;
	//sf::Vector2f m_position;	
};

