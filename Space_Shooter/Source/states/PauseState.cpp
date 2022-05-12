#include "pch.h"
#include "PauseState.h"
#include "Button.h"
#include "GuiFactory.h"
#include "Image.h"
#include "Label.h"


PauseState::PauseState(SharedContext aSharedContext)
	: State{ aSharedContext }
{
	InitButtonCallbacks();
	SetupGameUI();
}

PauseState::~PauseState()
{
}

void PauseState::HandleEvent(const sf::Event& aEvent)
{
	if (aEvent.type == sf::Event::KeyPressed && aEvent.key.code == sf::Keyboard::Escape)
	{
		RequestStackPop();
	}

	for (auto& element : m_graphicalElements)
	{
		element->HandleEvent(aEvent);
	}
}

void PauseState::Update(float aDeltaTime)
{
	for (auto& element : m_graphicalElements)
	{
		if (element->Update()) { return; }
	}
}

void PauseState::Render() const
{
	for (auto& element : m_graphicalElements)
	{
		element->Render();
	}
}

void PauseState::InitButtonCallbacks()
{
	m_buttonCallbacks[0] = [&]() { RequestStackPop(); };
	m_buttonCallbacks[1] = [&]() { RequestStackSwap(eStateType::Menu); };
}

void PauseState::SetupGameUI()
{
	auto images  = GuiFactory::GetInstance().CreateImages("pause");
	auto labels  = GuiFactory::GetInstance().CreateLabels("pause");
	auto buttons = GuiFactory::GetInstance().CreateButtons("pause");

	for (auto& button : buttons)
		button->AddCallback(m_buttonCallbacks[button->GetAction()]);

	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(images.begin()), std::make_move_iterator(images.end()));
	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(labels.begin()), std::make_move_iterator(labels.end()));
	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(buttons.begin()), std::make_move_iterator(buttons.end()));
}

void PauseState::Unpause()
{

}

void PauseState::ReturnToMainMenu()
{

}