#pragma once
#include "Label.h"
#include "Subscriber.h"
#include "Tilemap.h"

class Player;
class BulletSpawner;
class EnemySpawner;
class ObstacleSpawner;

class Level : public Subscriber
{
public:
	Level(BulletSpawner& aBulletSpawner, EnemySpawner& aEnemySpawner, ObstacleSpawner& aObstacleSpawner, Player& aPlayer, int aLevel);
	~Level();

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
	BulletSpawner&		m_bulletSpawner; // NEEDED HERE??
	EnemySpawner&		m_enemySpawner;
	ObstacleSpawner&	m_obstacleSpawner;
	Player&				m_player;
	//Label			m_currentLevelNotify; // Make notify class? Dispalay? Pop-up class?

	// PickupSpawner
	// Background...

	Tilemap m_tilemap;

	int m_enemiesDefeated;

	//	Label			m_levelText;
	unsigned 		m_levelIndex;
	bool			m_gameIsOver;

	sf::Clock		m_spawnTimer;
	
	//Player&					m_player;
	//Enemy&					m_enemy;
	// Wave class? - if all killed , extra points...	
};

