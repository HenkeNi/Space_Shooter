#pragma once
#include "Vector.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace CU = CommonUtilities;

struct BulletData
{
	CU::Vector2<float>	m_size;
	float				m_speed;
	int					m_damage;
	sf::Texture*		m_texture;
};