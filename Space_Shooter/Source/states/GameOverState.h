#pragma once
#include "State.h"

class Widget;

class GameOverState : public State
{
public:
	GameOverState(SharedContext aSharedContext);
	~GameOverState();

	virtual void	HandleEvent(const sf::Event& aEvent)	override;
	virtual void	Update(float aDeltaTime)				override;
	virtual void	Render()						  const override;

private:
	/* - Methods - */
	void			InitButtonCallbacks();
	void			SetupGameUI();

	std::vector<std::unique_ptr<Widget>> m_graphicalElements;
	std::array<std::function<void()>, 4>	m_buttonCallbacks;
};

