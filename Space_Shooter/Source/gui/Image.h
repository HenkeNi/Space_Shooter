#pragma once
#include "Widget.h"
#include "Vector.hpp"


namespace CU = CommonUtilities;

class Image : public Widget
{
public:
	Image(sf::RenderWindow& aWindow, const sf::Texture& aTexture);

	virtual void	HandleEvent(sf::Event aEvent)	override;
	virtual bool	Update()						override;
	virtual void	Render()				  const override;

	Image&			SetTexture(const sf::Texture& aTexture);
	Image&			SetPosition(const CU::Vector2<float>& aPosition);
	Image&			SetScale(const CU::Vector2<float>& aSize);

private:
	sf::Sprite		m_sprite;
};

