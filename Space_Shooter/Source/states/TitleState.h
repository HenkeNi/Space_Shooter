#pragma once
#include "State.h"
#include "Widget.h"


class TitleState : public State
{
public:
	TitleState(SharedContext aSharedContext);
	~TitleState();

	virtual void	HandleEvent(const sf::Event& aEvent)	override;
	virtual void	Update(float aDeltaTime)				override;
	virtual void	Render()						  const override;
	virtual void	OnEnter()								override;

private:
	/* -	Methods		- */
	void			SetupGameUI();
	bool			ShouldProceed();

	/* -	Members		- */
	std::vector<std::unique_ptr<Widget>>	m_graphicalElements;
	sf::Clock								m_clock;
	float									m_stateDuration;
	bool									m_shouldSkip;
};

