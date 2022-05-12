#include "pch.h"
#include "MenuState.h"
#include "Button.h"
#include "GuiFactory.h"
#include "Image.h"
#include "Label.h"


MenuState::MenuState(SharedContext aSharedContext)
	: State{ aSharedContext }
{
	InitButtonCallbacks();
	SetupGameUI();

	// ON enter... (set position and velocity...)

	// TODO: JSON array... position and velocity....
	m_sprite.setTexture(aSharedContext.m_textures.GetResource("EnemyShip"));
	m_sprite.setPosition(300.f, 0.5f);
}

MenuState::~MenuState()
{
}

void MenuState::HandleEvent(const sf::Event& aEvent)
{
	for (auto& element : m_graphicalElements)
	{
		element->HandleEvent(aEvent);
	}
}

void MenuState::Update(float aDeltaTime)
{
	for (auto& element : m_graphicalElements)
	{
		if (element->Update()) { return; }
	}

	UpdateDecorations();
}

void MenuState::Render() const
{
	for (auto& element : m_graphicalElements)
	{
		element->Render();
	}

	GetContext().m_window.draw(m_sprite);
}

void MenuState::InitButtonCallbacks()
{
	m_buttonCallbacks[0] = [&]() { RequestStackPop(); GetContext().m_levelManager.SetActiveLevel(1); GetContext().m_levelManager.OnLevelStart(); };
	m_buttonCallbacks[1] = [&]() { RequestStackSwap(eStateType::LevelSelect); };
	m_buttonCallbacks[2] = [&]() { RequestStackPush(eStateType::Settings); };
	m_buttonCallbacks[3] = [&]() { RequestStackClear(); };
}

void MenuState::SetupGameUI()
{
	auto images  = GuiFactory::GetInstance().CreateImages("main_menu");
	auto labels  = GuiFactory::GetInstance().CreateLabels("main_menu");
	auto buttons = GuiFactory::GetInstance().CreateButtons("main_menu");
	
	for (auto& button : buttons)
		button->AddCallback(m_buttonCallbacks[button->GetAction()]);
	
	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(images.begin()), std::make_move_iterator(images.end()));
	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(labels.begin()), std::make_move_iterator(labels.end()));
	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(buttons.begin()), std::make_move_iterator(buttons.end()));
}

void MenuState::UpdateDecorations()
{
	static bool random = false;
	m_sprite.move({ random ? -0.5f : 0.2f, 1.f });

	if (m_sprite.getPosition().y > 1000)
	{
		m_sprite.setPosition(300.f, 0.5f);
		random = !random;
	}
}
