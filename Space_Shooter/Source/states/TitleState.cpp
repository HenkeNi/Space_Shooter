#include "pch.h"
#include "TitleState.h"
#include "Image.h"
#include "Label.h"
#include "GuiFactory.h"


TitleState::TitleState(SharedContext aSharedContext)
	: State{ aSharedContext }, m_stateDuration{ 3.f }
{
	SetupGameUI();
}

TitleState::~TitleState()
{
}

void TitleState::HandleEvent(const sf::Event& aEvent)
{
	if (aEvent.type == sf::Event::KeyPressed || aEvent.type == sf::Event::MouseButtonReleased)
	{
		m_shouldSkip = true;
	}
}

void TitleState::Update(float aDeltaTime)
{
	for (auto& element : m_graphicalElements)
	{
		if (element->Update()) { return; }
	}

	if (m_shouldSkip || ShouldProceed())
	{
		RequestStackPop();
	}
}

void TitleState::Render() const
{
	for (auto& element : m_graphicalElements)
	{
		element->Render();
	}
}

void TitleState::OnEnter()
{
	m_clock.restart();
}

void TitleState::SetupGameUI()
{
	GuiFactory::GetInstance().SetContext(&GetContext());

	auto images = GuiFactory::GetInstance().CreateImages("title");
	auto labels = GuiFactory::GetInstance().CreateLabels("title");
	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(images.begin()), std::make_move_iterator(images.end()));
	m_graphicalElements.insert(m_graphicalElements.end(), std::make_move_iterator(labels.begin()), std::make_move_iterator(labels.end()));
}

bool TitleState::ShouldProceed()
{
	return m_clock.getElapsedTime().asSeconds() > m_stateDuration;
}
