#pragma once
#include "State.h"
#include "Widget.h"


class SettingsState : public State
{
public:
	SettingsState(SharedContext aSharedContext);
	~SettingsState();

	virtual void	HandleEvent(const sf::Event& aEvent)	override;
	virtual void	Update(float aDeltaTime)				override;
	virtual void	Render()						  const override;

private:
	/* - Methods - */
	void			InitButtonCallbacks();
	void			SetupGameUI();
	void			SetWindowSize(bool aStandard);

	/* - Members - */
	std::vector<std::unique_ptr<Widget>> m_graphicalElements;
	std::array<std::function<void()>, 3> m_buttonCallbacks; // Map??
};

