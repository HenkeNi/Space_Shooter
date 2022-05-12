#include "pch.h"
#include "LevelSelectState.h"
#include "Button.h"
#include "GuiFactory.h"
#include "Image.h"
#include "Label.h"


LevelSelectState::LevelSelectState(SharedContext aSharedContext)
	: State{ aSharedContext }
{
	InitButtonCallbacks();
	SetupGameUI();
}

LevelSelectState::~LevelSelectState()
{
}

void LevelSelectState::HandleEvent(const sf::Event& aEvent)
{
	for (auto& element : m_graphicalElements)
	{
		element->HandleEvent(aEvent);
	}
}

void LevelSelectState::Update(float aDeltaTime)
{
	for (auto& element : m_graphicalElements)
	{
		if (element->Update()) { return; }
	}

}

void LevelSelectState::Render() const
{
	for (auto& element : m_graphicalElements)
	{
		element->Render();
	}
}

void LevelSelectState::InitButtonCallbacks()
{
	m_buttonCallbacks[0] = [&]() { RequestStackSwap(eStateType::Menu); };
	m_buttonCallbacks[1] = [&]() { GetContext().m_levelManager.SetActiveLevel(1); RequestStackPop(); };
	m_buttonCallbacks[2] = [&]() { GetContext().m_levelManager.SetActiveLevel(2); RequestStackPop(); };
	m_buttonCallbacks[3] = [&]() { GetContext().m_levelManager.SetActiveLevel(3); RequestStackPop(); };
}

void LevelSelectState::SetupGameUI()
{
	auto images  = GuiFactory::GetInstance().CreateImages("level_select");
	auto labels  = GuiFactory::GetInstance().CreateLabels("level_select");
	auto buttons = GuiFactory::GetInstance().CreateButtons("level_select");

	for (auto& button : buttons)
		button->AddCallback(m_buttonCallbacks[button->GetAction()]);

	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(images.begin()), std::make_move_iterator(images.end()));
	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(labels.begin()), std::make_move_iterator(labels.end()));
	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(buttons.begin()), std::make_move_iterator(buttons.end()));
}