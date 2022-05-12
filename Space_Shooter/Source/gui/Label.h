#pragma once
#include "Widget.h"
#include "Vector.hpp"


namespace CU = CommonUtilities;

class Label : public Widget
{
public:
	Label(sf::RenderWindow& aWindow, const std::string& aText, const sf::Font& aFont, int aFontSize);

	virtual void	HandleEvent(sf::Event aEvent)	override;
	virtual bool	Update()						override;
	virtual void	Render()				  const override;

	Label&			SetText(const std::string& aText);
	Label&			SetStyle(int aStyle);
	Label&			SetPosition(const CU::Vector2<float>& aPosition);
	Label&			SetRotation(float aAngle);
	Label&			SetFillColor(const sf::Color& aColor);
	Label&			SetBorderThickness(float aThickness);
	Label&			SetBorderColor(sf::Color aColor);

private:
	/* - Methods - */
	void Init();

	/* - Members - */
	sf::Text m_text;
};

