#pragma once

class Agent;

class Command
{
public:
	virtual ~Command() = default;

	virtual void Execute(Agent& aAgent) = 0;
	virtual void Undo(Agent& aAgent)	 = 0;
};