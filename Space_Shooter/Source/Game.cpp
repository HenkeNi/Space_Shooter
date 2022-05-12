 #include "pch.h"
#include "Game.h"
#include "GameOverState.h"
#include "GameState.h"
#include "LevelSelectState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "SettingsState.h"
#include "TitleState.h"



Game::Game()
	: m_timePerFrame{ sf::seconds(1.f / 60.f) }
{
	LoadResources();

	InitWindow();
	RegisterStates();
	m_stateManager.Init();
}

Game::~Game()
{
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate{ sf::Time::Zero };

	/* - The Game Loop - */
	while (m_window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > m_timePerFrame)
		{
			timeSinceLastUpdate -= m_timePerFrame;

			ProcessEvents();
			Update(m_timePerFrame.asSeconds()); 
		}
		Render();
	}
}

void Game::ProcessEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
			break;
		}
		m_stateManager.HandleEvent(event);
	}
}
 
void Game::Update(float aDeltaTime)
{
	m_stateManager.Update(aDeltaTime);

	if (m_stateManager.IsEmpty())
	{
		m_window.close();
	}
}

void Game::Render()
{
	m_window.clear();
	m_stateManager.Render();

	m_window.setView(m_window.getDefaultView()); // ??
	m_window.display();
}

void Game::InitWindow()
{
	/* - Initialize window - */
	std::ifstream ifs{ "Assets/Json/Settings.json" };
	std::string content{ std::istreambuf_iterator<char>(ifs), (std::istreambuf_iterator<char>()) };

	rapidjson::Document document;
	if (document.Parse(content.c_str()).HasParseError())
	{
		std::cerr << "Error parsing \'Settings.json\'!\n";
	}
	
	auto windowSize = document["window"]["size"].GetObject();
	auto windowName = document["window"]["name"].GetString();

	m_window.create(sf::VideoMode(windowSize["width"].GetInt(), windowSize["height"].GetInt()), windowName);
}

void Game::RegisterStates()
{
	/* - Register states - */
	auto sharedContext = SharedContext{ m_window, m_levelManager, m_stateManager, m_textures, m_fonts };
	m_stateManager.RegisterState(std::make_unique<TitleState>(sharedContext),		eStateType::Title);
	m_stateManager.RegisterState(std::make_unique<MenuState>(sharedContext),		eStateType::Menu);
	m_stateManager.RegisterState(std::make_unique<GameState>(sharedContext),		eStateType::Game);
	m_stateManager.RegisterState(std::make_unique<SettingsState>(sharedContext),	eStateType::Settings);
	m_stateManager.RegisterState(std::make_unique<LevelSelectState>(sharedContext), eStateType::LevelSelect);
	m_stateManager.RegisterState(std::make_unique<PauseState>(sharedContext),		eStateType::Pause);
	m_stateManager.RegisterState(std::make_unique<GameOverState>(sharedContext),	eStateType::GameOver);
}

void Game::LoadResources()
{
	std::ifstream ifs{ "Assets/Json/Textures.json" };
	std::string	  content{ std::istreambuf_iterator<char>(ifs), (std::istreambuf_iterator<char>()) };

	rapidjson::Document document;
	if (document.Parse(content.c_str()).HasParseError()) { std::cerr << "Error parsing \'Textures.json\'!\n"; return; }

	const std::string path = document["directory"].GetString();
	for (auto& texture : document["textures"].GetArray())
	{
		m_textures.Load(texture["id"].GetString(), path + texture["path"].GetString());

	}

	/* - Fonts - */
	m_fonts.Load("fun_font",             "Assets/Fonts/font_fun.otf");

	/* - Sounds - */
}