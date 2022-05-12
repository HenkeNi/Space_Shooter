#pragma once
#include "AudioManager.h"
#include "LevelManager.h"
#include "StateManager.h"
#include "ResourceManager.hpp"


class Game : sf::NonCopyable
{
public:
	Game();
	~Game(); 

	void Run();

private:
	/* - Methods - */
	void ProcessEvents();
	void Update(float aDeltaTime);
	void Render();
	void InitWindow();
	void RegisterStates();
	void LoadResources();
	
	/* - Members - */
	AudioManager									m_audioManager;
	StateManager									m_stateManager;
	LevelManager									m_levelManager;
	ResourceManager<sf::Texture, std::string>		m_textures;
	ResourceManager<sf::Font, std::string>			m_fonts;
 	sf::RenderWindow								m_window;
	const sf::Time									m_timePerFrame;
};

