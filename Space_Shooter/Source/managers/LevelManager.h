#pragma once
#include "Level.h"
#include "Subscriber.h"


class LevelManager : public Subscriber
{
public:
	LevelManager();

	virtual void	Recieve(const Event& aEvent)				 override;
	bool			Update(float aDeltaTime);
	void			Render(sf::RenderTarget& aTarget)				const;

	void			RegisterLevel(std::unique_ptr<Level> aLevel);
	void			SetActiveLevel(int aLevel);
	
	bool ProceeedToNextLevel();
	void RestartLevel();

	void OnLevelStart();
	void OnLevelComplete();
	
private:
	/* - Members - */
	std::vector<std::unique_ptr<Level>>		m_levels;
	int										m_activeLevel;
};

