#include "pch.h"
#include "State.h"


State::State(SharedContext aSharedContext)
	: m_sharedContext{ aSharedContext }
{
}

void State::RequestStackPush(eStateType aState)
{
	auto& stateManager = m_sharedContext.m_stateManager;
	stateManager.PushState(aState);
}

void State::RequestStackPop()
{
	auto& stateManager = m_sharedContext.m_stateManager;
	stateManager.PopState();
}
void State::RequestStackClear()
{
	auto& stateManager = m_sharedContext.m_stateManager;
	stateManager.ClearStates();
}

void State::RequestStackSwap(eStateType aState)
{
	auto& stateManager = m_sharedContext.m_stateManager;
	stateManager.SwapState(aState);
}

const SharedContext& State::GetContext() const
{
	return m_sharedContext;
}