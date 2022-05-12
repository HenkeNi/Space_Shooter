#pragma once
#include "BulletData.h"
#include "eBulletType.h"
#include "SharedContext.h"

class Bullet;
class ColliderFactory;

class BulletFactory
{
public:
	BulletFactory(SharedContext aSharedContext, ColliderFactory& aColliderFactory);

	void	Init();
	Bullet* CreatePlayerBullet(int aType);
	Bullet* CreateEnemyBullet(int aType);

private:
	/* - Methods - */
	void	LoadBulletData();

	/* - Members - */
	std::array<BulletData, static_cast<int>(eBulletType::Count)>	m_bulletData; // TODO: fix connection to eBulletType
	SharedContext													m_sharedContext;
	ColliderFactory&												m_colliderFactory;
};

