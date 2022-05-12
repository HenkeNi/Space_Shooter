#pragma once
#include "Effect.h"
//#include "Player.h"

struct PickupData
{
	Effect*			m_effect;
	//std::function<void(Player& aPlayer)>	m_effect;
	float			m_durationInSecs;
	sf::Texture*	m_texture;
};

