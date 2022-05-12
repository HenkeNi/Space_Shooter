#include "pch.h"
#include "GameOverState.h"
#include "Button.h"
#include "GuiFactory.h"
#include "Image.h"
#include "Label.h"


GameOverState::GameOverState(SharedContext aSharedContext)
	: State{ aSharedContext }
{
	InitButtonCallbacks();
	SetupGameUI();
}

GameOverState::~GameOverState()
{
}

void GameOverState::HandleEvent(const sf::Event& aEvent)
{
	for (auto& element : m_graphicalElements)
	{
		element->HandleEvent(aEvent);
	}
}

void GameOverState::Update(float aDeltaTime)
{
	for (auto& element : m_graphicalElements)
	{
		if (element->Update()) { return; }
	}
}

void GameOverState::Render() const
{
	for (auto& element : m_graphicalElements)
	{
		element->Render();
	}
}

void GameOverState::InitButtonCallbacks()
{
	m_buttonCallbacks[0] = [&]() { GetContext().m_levelManager.RestartLevel(); RequestStackPop(); }; // Restart level...
	m_buttonCallbacks[1] = [&]() { RequestStackSwap(eStateType::Menu); };
}

void GameOverState::SetupGameUI()
{
	auto images  = GuiFactory::GetInstance().CreateImages("game_over");
	auto labels  = GuiFactory::GetInstance().CreateLabels("game_over");
	auto buttons = GuiFactory::GetInstance().CreateButtons("game_over");

	for (auto& button : buttons)
		button->AddCallback(m_buttonCallbacks[button->GetAction()]);

	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(images.begin()), std::make_move_iterator(images.end()));
	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(labels.begin()), std::make_move_iterator(labels.end()));
	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(buttons.begin()), std::make_move_iterator(buttons.end()));
}
