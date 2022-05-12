#include "pch.h"
#include "GameState.h"
#include "PauseState.h"
#include "Dispatcher.h"



GameState::GameState(SharedContext aSharedContext)
	: State{ aSharedContext }, 
	  m_agentFactory{ aSharedContext, m_colliderFactory }, 
	  m_bulletFactory{ aSharedContext, m_colliderFactory }, 
 	  m_entityManager{ aSharedContext.m_window },
	  m_bulletSpawner{ m_bulletFactory },
	  m_enemySpawner{ m_agentFactory },
	  m_pickupFactory{ aSharedContext, m_colliderFactory },
	  m_pickupSpawner{ m_pickupFactory }
{
	Init();
	RegisterLevels();

	Dispatcher::GetInstance().Subscribe(eEvent::PlayerDeath, this);
}

GameState::~GameState()
{
	Dispatcher::GetInstance().Unsubscribe(eEvent::PlayerDeath, this);
}

void GameState::Recieve(const Event& aEvent)
{
	switch (aEvent.GetEventType())
	{
	case eEvent::PlayerDeath:
		RequestStackPush(eStateType::GameOver);
		break;
	}
}

void GameState::HandleEvent(const sf::Event& aEvent)
{
	m_player->HandleInput();


	if (ShouldPause(aEvent))
		RequestStackPush(eStateType::Pause);
}

void GameState::Update(float aDeltaTime)
{
	m_player->Update(aDeltaTime);	

	GetContext().m_levelManager.Update(aDeltaTime);

	//if (GetContext().m_levelManager.Update(aDeltaTime))
	//{
	//	// RESET GAME?!
	//	m_player->Respawn(); 
	//	RequestStackPush(eStateType::GameOver);
	//	//RequestStackSwap(eStateType::GameOver);
	//}

	m_entityManager.Update(aDeltaTime);
	m_collisionManager.Update(aDeltaTime);
	m_HUD.Update(aDeltaTime);
}

void GameState::Render() const 
{
	auto& window = GetContext().m_window;

	GetContext().m_levelManager.Render(window);
	m_entityManager.Render(window);

	if (m_player)
		m_player->Render(window);

	m_HUD.Render(window);
}

void GameState::OnEnter()
{
	// CALLED EVERY TIME GameState comes active (after pause, etc...)

	// ENter Level...
	std::cout << "Starting Game..\n";
}

void GameState::Init()
{
	m_entityManager.Init();
	m_collisionManager.Init();
	m_agentFactory.Init();
	m_bulletFactory.Init();
	m_pickupFactory.Init();

	m_player = m_agentFactory.CreatePlayer(1);

	auto windowSize = GetContext().m_window.getSize();
	m_player->Init({ windowSize.x * 0.5f, windowSize.y * 0.8f });





	m_HUD.Init(GetContext(), m_player);
}

void GameState::RegisterLevels()
{
	// TODO: Load data from JSON??

	auto level1 = std::make_unique<Level>(m_bulletSpawner, m_enemySpawner, *m_player, 1);
	auto level2 = std::make_unique<Level>(m_bulletSpawner, m_enemySpawner, *m_player, 2);
	auto level3 = std::make_unique<Level>(m_bulletSpawner, m_enemySpawner, *m_player, 3);
	
	Dispatcher::GetInstance().Subscribe(eEvent::PlayerDeath, level1.get());
	Dispatcher::GetInstance().Subscribe(eEvent::PlayerDeath, level2.get());
	Dispatcher::GetInstance().Subscribe(eEvent::PlayerDeath, level3.get());

	Dispatcher::GetInstance().Subscribe(eEvent::EnemyDeath, level1.get());
	Dispatcher::GetInstance().Subscribe(eEvent::EnemyDeath, level2.get());
	Dispatcher::GetInstance().Subscribe(eEvent::EnemyDeath, level3.get());

	GetContext().m_levelManager.RegisterLevel(std::move(level1));
	GetContext().m_levelManager.RegisterLevel(std::move(level2));
	GetContext().m_levelManager.RegisterLevel(std::move(level3));

	//GetContext().m_levelManager.RegisterLevel(std::make_unique<Level>(m_bulletSpawner, m_enemySpawner, 1));
	//GetContext().m_levelManager.RegisterLevel(std::make_unique<Level>(m_bulletSpawner, m_enemySpawner, 2));
	//GetContext().m_levelManager.RegisterLevel(std::make_unique<Level>(m_bulletSpawner, m_enemySpawner, 3));
}

bool GameState::ShouldPause(const sf::Event aEvent) const
{
	return aEvent.type == sf::Event::KeyPressed && aEvent.key.code == sf::Keyboard::Escape;
}
