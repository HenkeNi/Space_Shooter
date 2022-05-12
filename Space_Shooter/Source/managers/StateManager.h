#pragma once
#include "eStateType.h"

class State;

class StateManager
{
public:
	StateManager();

	void HandleEvent(const sf::Event& aEvent);
	void Update(float aDeltaTime);
	void Render() const;

	void RegisterState(std::unique_ptr<State> aState, eStateType aType);
	void PushState(eStateType aType);
	void PopState();
	void ClearStates();
	void SwapState(eStateType aType);
	void Init();
	
	bool IsEmpty() const;

private:	
	std::stack<eStateType>													m_stateStack;
	std::array<std::unique_ptr<State>, static_cast<int>(eStateType::Count)>	m_states;
};