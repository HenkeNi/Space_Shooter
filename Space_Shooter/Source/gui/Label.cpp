#include "pch.h"
#include "Label.h"



Label::Label(sf::RenderWindow& aWindow, const std::string& aText, const sf::Font& aFont, int aFontSize)
	: Widget{ aWindow }, m_text{ aText, aFont, aFontSize }
{
	Init();
}

void Label::HandleEvent(sf::Event aEvent)
{
}

bool Label::Update()
{
	return false;
}

void Label::Render() const
{
	m_window.draw(m_text);
}

Label& Label::SetText(const std::string& aText)
{
	m_text.setString(aText);
	return *this;
}

Label& Label::SetStyle(int aStyle)
{
	m_text.setStyle(1 << aStyle);
	return *this;
}

Label& Label::SetPosition(const CU::Vector2<float>& aPosition)
{
	m_text.setPosition({ aPosition.x, aPosition.y });
	return *this;
}

Label& Label::SetRotation(float aAngle)
{
	m_text.setRotation(aAngle);
	return *this;
}

Label& Label::SetFillColor(const sf::Color& aColor)
{
	m_text.setFillColor(aColor);
	return *this;
}

Label& Label::SetBorderThickness(float aThickness)
{
	m_text.setOutlineThickness(aThickness);
	return *this;
}

Label& Label::SetBorderColor(sf::Color aColor)
{
	m_text.setOutlineColor(aColor);
	return *this;
}

void Label::Init() 
{
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width * 0.5f, textRect.top + textRect.height * 0.5f);
}