#pragma once
#include "AgentFactory.h"
#include "BulletFactory.h"
#include "BulletSpawner.h"
#include "ColliderFactory.h"
#include "CollisionManager.h"
#include "EnemySpawner.h"
#include "PickupSpawner.h"
#include "PickupFactory.h"
#include "ObstacleFactory.h"
#include "ObstacleSpawner.h"
#include "EntityManager.h"
#include "HUD.h"
#include "Player.h"
#include "State.h"


class GameState : public State, public Subscriber
{
public:
	GameState(SharedContext aSharedContext);
	~GameState();

	virtual void		Recieve(const Event& aEvent)					override;
	virtual void		HandleEvent(const sf::Event& aEvent)			override;
	virtual void		Update(float aDeltaTime)						override;
	virtual void		Render()								const	override;
	virtual void		OnEnter()										override;

private:
	/* - Methods - */
	void				Init();
	void				RegisterLevels();
	bool				ShouldPause(const sf::Event aEvent)				   const;
	
	/* - Members - */
	AgentFactory		m_agentFactory;
	BulletFactory		m_bulletFactory;
	BulletSpawner		m_bulletSpawner;
	ColliderFactory		m_colliderFactory;
	CollisionManager	m_collisionManager;
	EnemySpawner		m_enemySpawner;
	EntityManager		m_entityManager;
	HUD					m_HUD;
	
	ObstacleFactory m_obstacleFactory;
	ObstacleSpawner m_obstacleSpawner;  // Combine with enemies??

	Player*				m_player;
	PickupFactory		m_pickupFactory;
	PickupSpawner		m_pickupSpawner;
	//sf::FloatRect		m_worldBounds;
};

