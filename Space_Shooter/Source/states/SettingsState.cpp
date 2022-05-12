#include "pch.h"
#include "SettingsState.h"
#include "Button.h"
#include "GuiFactory.h"
#include "Image.h"
#include "Label.h"


SettingsState::SettingsState(SharedContext aSharedContext)
	: State{ aSharedContext }
{
	InitButtonCallbacks();
	SetupGameUI();
}

SettingsState::~SettingsState()
{
}

void SettingsState::HandleEvent(const sf::Event& aEvent)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		GetContext().m_window.create(sf::VideoMode(1024, 720), "Window Changed");
		std::cout << "A\n";
	}



	for (auto& element : m_graphicalElements)
	{
		element->HandleEvent(aEvent);
	}
}

void SettingsState::Update(float aDeltaTime)
{
	for (auto& element : m_graphicalElements)
	{
		if (element->Update()) { return; }
	}
}

void SettingsState::Render() const
{
	for (auto& element : m_graphicalElements)
	{
		element->Render();
	}
}

void SettingsState::InitButtonCallbacks()
{
	m_buttonCallbacks[0] = [&]() { SetWindowSize(false); };
	m_buttonCallbacks[1] = [&]() { SetWindowSize(true);  };
	m_buttonCallbacks[2] = [&]() { RequestStackPop();	 };

}

void SettingsState::SetupGameUI()
{
	auto images  = GuiFactory::GetInstance().CreateImages("settings");
	auto labels  = GuiFactory::GetInstance().CreateLabels("settings");
	auto buttons = GuiFactory::GetInstance().CreateButtons("settings");

	for (auto& button : buttons)
		button->AddCallback(m_buttonCallbacks[button->GetAction()]);

	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(images.begin()), std::make_move_iterator(images.end()));
	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(labels.begin()), std::make_move_iterator(labels.end()));
	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(buttons.begin()), std::make_move_iterator(buttons.end()));
}

void SettingsState::SetWindowSize(bool aStandard)
{
	GetContext().m_window.create(sf::VideoMode(aStandard ? 640 : 1024, aStandard ? 480 : 720), "New window!!!!!!");
}
