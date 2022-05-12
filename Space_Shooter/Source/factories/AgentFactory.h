#pragma once
#include "SharedContext.h"
#include "eAgentType.h"
#include "AgentData.h"
#include "ColliderFactory.h"
#include "eWeaponType.h"
#include "WeaponData.h"

class Boss;
class Enemy;
class Player;
class Weapon;

using AgentData_t  = std::array<AgentData, static_cast<int>(eAgentType::Count)>;
using WeaponData_t = std::array<WeaponData, static_cast<int>(eAgentType::Count)>;

class AgentFactory
{
public:
	AgentFactory(SharedContext aSharedContext, ColliderFactory& aColliderFactory);

	void					Init();
	Boss*					CreateBoss(int aType);
	Enemy*					CreateEnemy(int aType);
	Player*					CreatePlayer(int aType);

private:
	/* - Methods - */
	void					LoadAgentData();
	void					LoadWeaponData();
	std::unique_ptr<Weapon> CreateWeapon(eWeaponType aType, bool isPlayer);

	/* - Members - */
	AgentData_t				m_agentData;
	WeaponData_t			m_weaponData;
	SharedContext			m_sharedContext;
	ColliderFactory&		m_colliderFactory;
};

