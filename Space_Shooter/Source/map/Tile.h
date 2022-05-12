#pragma once
#include "Vector.hpp"


namespace CU = CommonUtilities;

class Tile
{
public:
	enum class eTileType // Put in enums
	{
		Wall, Spike, Count 
	};

	void Render(sf::RenderTarget& aTarget);

private:
	sf::Sprite	m_sprite;
	CU::Vector2<float> m_position;
	CU::Vector2<float> m_size;
	eTileType	m_type;
	bool		m_collidable; // Pointer instead to collidable?
};

