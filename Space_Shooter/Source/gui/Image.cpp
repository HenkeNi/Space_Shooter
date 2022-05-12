#include "pch.h"
#include "Image.h"


Image::Image(sf::RenderWindow& aWindow, const sf::Texture& aTexture)
	: Widget{ aWindow }, m_sprite { aTexture }
{
}

void Image::HandleEvent(sf::Event aEvent)
{
}

bool Image::Update()
{
	return false;
}

void Image::Render() const
{
	m_window.draw(m_sprite);
}

Image& Image::SetTexture(const sf::Texture& aTexture)
{
	m_sprite.setTexture(aTexture);
	return *this;
}

Image& Image::SetPosition(const CU::Vector2<float>& aPosition)
{
	m_sprite.setPosition({ aPosition.x, aPosition.y });
	return *this;
}

Image& Image::SetScale(const CU::Vector2<float>& aSize)
{
	m_sprite.setScale({ aSize.x, aSize.y });
	return *this;
}