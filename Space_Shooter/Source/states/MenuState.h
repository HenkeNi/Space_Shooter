#pragma once
#include "State.h"
#include "Widget.h"


class MenuState : public State
{
public:
	MenuState(SharedContext aSharedContext);
	~MenuState();

	virtual void	HandleEvent(const sf::Event& aEvent)	override;
	virtual void	Update(float aDeltaTime)				override;
	virtual void	Render()						  const override;

private:
	/* - Methods - */
	void			InitButtonCallbacks();
	void			SetupGameUI();
	void			UpdateDecorations();

	/* - Members - */
	std::vector<std::unique_ptr<Widget>>	m_graphicalElements;
	std::array<std::function<void()>, 4>	m_buttonCallbacks;
	std::array<sf::Sprite, 2>				m_decorations;
	sf::Sprite								m_sprite;
};

