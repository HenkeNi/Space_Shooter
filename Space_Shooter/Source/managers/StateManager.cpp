#include "pch.h"
#include "StateManager.h"
#include "State.h"



StateManager::StateManager()
{
}

void StateManager::HandleEvent(const sf::Event& aEvent)
{
	if (!IsEmpty())
		m_states[static_cast<int>(m_stateStack.top())]->HandleEvent(aEvent);
}

void StateManager::Update(float aDeltaTime)
{
	if (!IsEmpty())
		m_states[static_cast<int>(m_stateStack.top())]->Update(aDeltaTime);
}

void StateManager::Render() const
{
	if (!IsEmpty())
		m_states[static_cast<int>(m_stateStack.top())]->Render();
}

void StateManager::RegisterState(std::unique_ptr<State> aState, eStateType aType)
{
	m_states[static_cast<int>(aType)] = std::move(aState);
}

void StateManager::PushState(eStateType aType)
{
	m_stateStack.push(aType);
	m_states[static_cast<int>(m_stateStack.top())]->OnEnter();
}

void StateManager::PopState()
{
	if (!m_stateStack.empty())
	{
		m_states[static_cast<int>(m_stateStack.top())]->OnExit();
		m_stateStack.pop();
		m_states[static_cast<int>(m_stateStack.top())]->OnEnter();
	}
}

void StateManager::ClearStates()
{
	while (!m_stateStack.empty())
		m_stateStack.pop();
}

void StateManager::SwapState(eStateType aType)
{
	m_states[static_cast<int>(m_stateStack.top())]->OnExit();
	m_stateStack.pop();
	m_stateStack.push(aType);
	m_states[static_cast<int>(m_stateStack.top())]->OnEnter();
}

bool StateManager::IsEmpty() const
{
	return m_stateStack.empty();
}

void StateManager::Init()
{
	m_stateStack.push(eStateType::Game);
	m_stateStack.push(eStateType::Menu);
	m_stateStack.push(eStateType::Title);
}