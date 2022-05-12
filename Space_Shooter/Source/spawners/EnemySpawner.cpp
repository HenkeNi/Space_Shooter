#include "pch.h"
#include "EnemySpawner.h"
#include "Boss.h"
#include "Enemy.h"
#include "AgentFactory.h"
#include "Dispatcher.h"


EnemySpawner::EnemySpawner(AgentFactory& aAgentFactory)
	: m_agentFactory{ aAgentFactory }
{
}

void EnemySpawner::Update(float aDeltaTime)
{

}

void EnemySpawner::SpawnEnemy(const CU::Vector2<float>& aPosition)
{
	Enemy* enemy = m_agentFactory.CreateEnemy(0);
	enemy->SetPosition(aPosition);
	enemy->SetVelocity({ 0.f, 1.f });
	//enemy->SetVelocity({ 0.f, 0.01f });

	//Dispatcher::GetInstance().SendEvent(Event{ eEvent::EnemyCreated, enemy });
}

void EnemySpawner::SpawnBoss(const CU::Vector2<float>& aPosition)
{
	Boss* boss = m_agentFactory.CreateBoss(2);
	boss->SetPosition(aPosition);
	boss->SetVelocity({ 0.f, 0.01f });
}