#pragma once
#include "SharedContext.h"
#include "eStateType.h"


class State
{
public:
	State(SharedContext aSharedContext);
	virtual ~State() = default;

	virtual void			HandleEvent(const sf::Event& aEvent)	= 0;
	virtual void			Update(float aDeltaTime)				= 0;
	virtual void			Render() const							= 0;
	virtual void			OnEnter() {};
	virtual void			OnExit()  {};

protected:
	/* - Methods - */
	void					RequestStackPush(eStateType aState);
	void					RequestStackPop();
	void					RequestStackClear();
	void					RequestStackSwap(eStateType aState);
	const SharedContext&	GetContext() const;

private:
	/* - Members - */
	SharedContext			m_sharedContext;
};