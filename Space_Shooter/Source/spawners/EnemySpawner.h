#pragma once
#include "Vector.hpp"

namespace CU = CommonUtilities;

class AgentFactory;

class EnemySpawner
{
public:
	EnemySpawner(AgentFactory& aAgentFactory);
	
	void Update(float aDeltaTime);

	void SpawnEnemy(const CU::Vector2<float>& aPosition);
	void SpawnBoss(const CU::Vector2<float>& aPosition);
	// spawnWave
	// SpawnBoss
	

private:
	AgentFactory&	m_agentFactory;
};

