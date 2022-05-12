#pragma once
#include "State.h"
#include "Widget.h"


class PauseState : public State
{
public:
	PauseState(SharedContext aSharedContext);
	~PauseState();

	virtual void	HandleEvent(const sf::Event& aEvent)	override;
	virtual void	Update(float aDeltaTime)				override;
	virtual void	Render()						  const override;

private:
	/* - Methods - */
	void			InitButtonCallbacks();
	void			SetupGameUI();
	void			Unpause();
	void			ReturnToMainMenu();

	/* - Members - */
	std::vector<std::unique_ptr<Widget>> m_graphicalElements;
	std::array<std::function<void()>, 2>	m_buttonCallbacks;
};

