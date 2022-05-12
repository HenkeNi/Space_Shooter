#pragma once
#include "Command.h"
#include "eMoveDir.h"


class MoveCommand : public Command
{
public:
	virtual void	Execute(Agent& aAgent)		override;
	virtual void	Undo(Agent& aAgent)		override;

private:
	eMoveDir		m_direction;
};



//class FireCommand : public Command
//{
//public:
//	virtual void Execute(Agent& anAgent) override;
//
//};

