#pragma once

class Widget 
{
public:
	Widget(sf::RenderWindow& aWindow);

	virtual			~Widget() = default;
	virtual void	HandleEvent(sf::Event aEvent)	= 0;
	virtual bool	Update()						= 0;
	virtual void	Render() const					= 0;

protected:
	sf::RenderWindow&	m_window;
};

