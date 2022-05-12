#pragma once
#include "Widget.h"
#include "Vector.hpp"
#include "AABB2D.hpp"

namespace CU = CommonUtilities;

class Button : public Widget
{
public:
	enum class State
	{
		Idle, Hover, Clicked
	};

	Button(sf::RenderWindow& aWindow, const std::string& aText, const sf::Font& aFont, int aFontSize);

	virtual void	HandleEvent(sf::Event aEvent)	override;
	virtual bool	Update()						override;
	virtual void	Render()				  const override;

	void			Center();
	void			SetPosition(const CU::Vector2<float>& aPosition);
	void			SetSize(const CU::Vector2<float>& aSize);
	void			SetContainerColor(sf::Color aColor);
	void			SetTextColor(sf::Color aColor);
	void			SetBorderThickness(float aThickness);
	void			SetBorderColor(sf::Color aColor);
	void			SetAction(int aAction);
	void			AddCallback(std::function<void()> aCallback);


	void loadFromFile();
	
	int GetAction() const;

private:
	/* - Methods - */
	void			Init();
	void			ExecuteCallback();
	void			UpdateButtonColor(bool isContainingMouse);
	bool			ContainsMouse(const CU::Vector2<int>& aMousePos);

	/* - Members - */
	CU::AABB2D<float> m_bounds; // TODO: FIX!


	std::vector<std::function<void()>>	m_callbacks;
	sf::RectangleShape					m_container;
	sf::Color							m_containerColor; // Union Container color and Hover color?
	sf::Text							m_text; // Label instead??
	State								m_state;
	int									m_action;
	bool								m_isClicked;
	bool								m_containsMouse;
};

