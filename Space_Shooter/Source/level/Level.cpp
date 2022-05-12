#include "pch.h"
#include "Level.h"
#include "BulletSpawner.h"
#include "EnemySpawner.h"
#include "Dispatcher.h"
#include "UtilityFunctions.hpp"

#include "Player.h"

namespace CU = CommonUtilities;


Level::Level(BulletSpawner& aBulletSpawner, EnemySpawner& aEnemySpawner, Player& aPlayer, int aLevel)
	: m_bulletSpawner{ aBulletSpawner }, m_enemySpawner{ aEnemySpawner }, m_player{ aPlayer }, m_levelIndex{ GenerateId() }, m_gameIsOver{ false }, m_enemiesDefeated{ 0 }
{
	Init();
}

void Level::Recieve(const Event& aEvent)
{
	switch (aEvent.GetEventType())
	{
		case eEvent::PlayerDeath: // Listen to enemies killedd????? - listen in GameState instead?
			m_gameIsOver = true;
			break;
		case eEvent::EnemyDeath:
  			++m_enemiesDefeated;
			break;
	}
}

bool Level::Update(float aDeltaTime)
{
	//std::cout << "Level: " << m_levelIndex << '\n';

	//SpawnEnemies();



	if (IsLevelComplete())
	{
		// Send Notify that level is complete...
	}


	//if (m_spawnTimer.getElapsedTime().asSeconds() > 0.1f)// m_spawnDelay)
	//{
	//	SpawnEnemies();
	//	m_spawnTimer.restart();		
	//}
	//return IsLevelComplete();
	return m_gameIsOver;
}

void Level::Render(sf::RenderTarget& aTarget) const
{
	// Render background...
	//m_levelText.Render();
}


void Level::OnStart()
{


	std::cout << "Level " << m_levelIndex << " started!\n";

	// INIT PLAYER??
	//m_player.Respawn();


	m_enemySpawner.SpawnBoss({ 200.f, 200.f });

	//m_enemySpawner.SpawnEnemy({ 200.5f, 200.5f });



}

unsigned Level::GenerateId() const
{
	static int id{ 0 };
	return id++;
}

void Level::Init()
{


	//Dispatcher::GetInstance().Subscribe(eEvent::PlayerFire, &m_bulletSpawner);

	//m_levelText.SetText("Level" + std::to_string(m_level));
	//m_levelText.SetFillColor(sf::Color::Red);
	//m_levelText.SetPosition({ 200.f, 200.f });

	
	//m_player.Respawn();
}

void Level::SpawnEnemies()
{
	static sf::Clock spawnTimer;
	if (spawnTimer.getElapsedTime() > sf::seconds(2.f))
	{
		int random = CU::GetRandomNumber<int>(50, 700); 
		m_enemySpawner.SpawnEnemy({ (float)random, -1.2f });
		
		spawnTimer.restart();
	}
}

bool Level::IsLevelComplete() const
{
	return m_enemiesDefeated > 3;
}

void Level::Restart()
{
	// TODO: Show Level Label... (LARGE)!

	// TODO: listen to Player dead...?
	m_player.Respawn();
}