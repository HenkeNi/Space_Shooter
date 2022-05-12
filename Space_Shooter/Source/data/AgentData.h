#pragma once
#include "Vector.hpp"

namespace CU = CommonUtilities;

struct AgentData
{
	CU::Vector2<float>					m_size;
	std::vector<int>					m_weaponIds;
	float								m_movementSpeed;
	int									m_maxHealth;
	std::vector<sf::Texture*>			m_textures;
};