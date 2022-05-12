#pragma once
#include "Label.h"
#include "Subscriber.h"
#include "Tilemap.h"

class Player;
class BulletSpawner;
class EnemySpawner;

class Level : public Subscriber
{
public:
	Level(BulletSpawner& aBulletSpawner, EnemySpawner& aEnemySpawner, Player& aPlayer, int aLevel);

	virtual void	Recieve(const Event& aEvent)	override;

	bool Update(float aDeltaTime);
	void Render(sf::RenderTarget& aTarget) const;

	void OnStart();
	void Restart();

	unsigned GenerateId() const;

private:
	/* - Methods - */
	void Init();
	void SpawnEnemies();
	bool IsLevelComplete() const;

	/* - Members - */
	BulletSpawner&	m_bulletSpawner; // NEEDED HERE??
	EnemySpawner&	m_enemySpawner;
	Player&			m_player;
	//Label			m_currentLevelNotify; // Make notify class? Dispalay? Pop-up class?

	// PickupSpawner
	// Background...

	Tilemap m_tilemap;

	int m_enemiesDefeated;

	//	Label			m_levelText;
	unsigned 		m_levelIndex;
	bool			m_gameIsOver;
	
	//Player&					m_player;
	//Enemy&					m_enemy;
	// Wave class? - if all killed , extra points...	
};

