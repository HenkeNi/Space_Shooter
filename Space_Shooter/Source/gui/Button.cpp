#include "pch.h"
#include "Button.h"



Button::Button(sf::RenderWindow& aWindow, const std::string& aText, const sf::Font& aFont, int aFontSize)
	: Widget{ aWindow }, m_text{ aText, aFont, aFontSize }
{
	Init();
}

void Button::HandleEvent(sf::Event aEvent)
{
	if (aEvent.type == sf::Event::MouseButtonReleased && m_containsMouse)
	{
		ExecuteCallback();
		m_isClicked = true;
	}
}

bool Button::Update()
{
	auto pos = sf::Mouse::getPosition(m_window);
	m_containsMouse = ContainsMouse({ pos.x, pos.y });
	UpdateButtonColor(m_containsMouse);

	return m_isClicked;
}

void Button::Render() const
{
	m_window.draw(m_container);
	m_window.draw(m_text);
}

void Button::Center()
{
	auto containerRect = m_container.getLocalBounds();
	m_container.setOrigin(containerRect.left + containerRect.width * 0.5f, containerRect.top + containerRect.height * 0.5f);

	auto textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width * 0.5f, textRect.top + textRect.height * 0.5f);
}

void Button::SetPosition(const CU::Vector2<float>& aPosition)
{
	m_container.setPosition({ aPosition.x, aPosition.y });
	m_text.setPosition({ aPosition.x, aPosition.y });
}

void Button::SetSize(const CU::Vector2<float>& aSize)
{
	m_container.setSize({ aSize.x, aSize.y });
}

void Button::SetContainerColor(sf::Color aColor)
{
	m_containerColor = aColor;
	m_container.setFillColor(aColor);
}

void Button::SetTextColor(sf::Color aColor)
{
	m_text.setFillColor(aColor);
}

void Button::SetBorderThickness(float aThickness)
{
	m_container.setOutlineThickness(aThickness);
}

void Button::SetBorderColor(sf::Color aColor)
{
	m_container.setOutlineColor(aColor);
}

void Button::SetAction(int aAction)
{
	m_action = aAction;
}

void Button::AddCallback(std::function<void()> aCallback)
{
	m_callbacks.push_back(aCallback);
}

int Button::GetAction() const
{
	return m_action;
}

void Button::ExecuteCallback()
{
	m_callbacks.back()();
}

void Button::Init()
{
}

void Button::UpdateButtonColor(bool isContainingMouse)
{
	if (isContainingMouse)
	{
		m_container.setFillColor(sf::Color(m_containerColor.r * 0.5f, m_containerColor.g * 0.5f, m_containerColor.b * 0.5f, m_containerColor.a));
	}
	else
	{
		m_container.setFillColor(m_containerColor);
	}
}

bool Button::ContainsMouse(const CU::Vector2<int>& aMousePos)
{
	return m_container.getGlobalBounds().contains(aMousePos.x, aMousePos.y);
}