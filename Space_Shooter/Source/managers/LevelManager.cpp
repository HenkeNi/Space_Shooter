#include "pch.h"
#include "LevelManager.h"



LevelManager::LevelManager()
	: m_activeLevel{ 1 }
{
}

void LevelManager::Recieve(const Event& aEvent)
{
	switch (aEvent.GetEventType())
	{
	case eEvent::LevelCompleted:
		OnLevelComplete();
		break;
	}
}

bool LevelManager::Update(float aDeltaTime)
{
	return m_levels[m_activeLevel - 1]->Update(aDeltaTime);
}

void LevelManager::Render(sf::RenderTarget& aTarget) const
{
	m_levels[m_activeLevel - 1]->Render(aTarget);
}

void LevelManager::RegisterLevel(std::unique_ptr<Level> aLevel)
{
	m_levels.push_back(std::move(aLevel));
}

void LevelManager::SetActiveLevel(int aLevel)
{
	assert(aLevel > 0 && aLevel <= 3);
	m_activeLevel = aLevel;
}

bool LevelManager::ProceeedToNextLevel()
{
	if ((++m_activeLevel) >= m_levels.size())
	{
		return false;
	}
	return true;
}

void LevelManager::RestartLevel()
{
	m_levels[m_activeLevel]->Restart();
}

void LevelManager::OnLevelStart()
{
	m_levels[m_activeLevel]->OnStart();
}

void LevelManager::OnLevelComplete()
{
	// INcrement to next level (if any...) .. send notification..
}
