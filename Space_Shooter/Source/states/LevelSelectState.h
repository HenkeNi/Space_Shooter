#pragma once
#include "State.h"
#include "Widget.h"


class LevelSelectState : public State
{
public:
	LevelSelectState(SharedContext aSharedContext);
	~LevelSelectState();

	virtual void	HandleEvent(const sf::Event& aEvent)	override;
	virtual void	Update(float aDeltaTime)				override;
	virtual void	Render()						  const override;

private:
	/* - Methods - */
	void			InitButtonCallbacks();
	void			SetupGameUI();

	/* - Members - */
	std::vector<std::unique_ptr<Widget>>	m_graphicalElements;
	std::array<std::function<void()>, 4>	m_buttonCallbacks;
};

