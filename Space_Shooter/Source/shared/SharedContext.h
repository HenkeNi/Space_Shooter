#pragma once
#include "LevelManager.h"
#include "ResourceManager.hpp"
#include "StateManager.h"

#include <SFML/Graphics.hpp>

struct SharedContext
{
	/* - Window - */
	sf::RenderWindow&							m_window;

	/* - Managers - */
	LevelManager&								m_levelManager;
	StateManager&								m_stateManager;
	ResourceManager<sf::Texture, std::string>&	m_textures;
	ResourceManager<sf::Font,    std::string>&	m_fonts;
};