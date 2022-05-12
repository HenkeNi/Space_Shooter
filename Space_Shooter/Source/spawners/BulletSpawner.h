 #pragma once
#include "Subscriber.h"
#include "Vector.hpp"

class BulletFactory;

namespace CU = CommonUtilities;

class BulletSpawner : public Subscriber
{
public:
	BulletSpawner(BulletFactory& aFactory);
	~BulletSpawner();

	virtual void Recieve(const Event& aEvent)	override;

private:
	void SpawnPlayerBullet(const std::tuple<CU::Vector2<float>, CU::Vector2<float>> someBulletData);
	void SpawnPlayerBullet(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aVelocity);
	void SpawnEnemyBullet(const std::tuple<CU::Vector2<float>, CU::Vector2<float>> someBulletData);
	void SpawnEnemyBullet(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aVelocity);

	//void SpawnBulletPattern();

	/* - Members - */
	BulletFactory&		m_bulletFactory;
	// EntityManager&		m_entityManager;
};

