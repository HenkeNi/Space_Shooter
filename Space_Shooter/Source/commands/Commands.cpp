#include "pch.h"
#include "Commands.h"
#include "Agent.h"


void MoveCommand::Execute(Agent& aAgent)
{
	sf::Vector2f velocity;

	switch (m_direction)
	{
	case eMoveDir::Left:
		velocity.x = -1.f;
		break;
	case eMoveDir::Right:
		velocity.x = 1.f;
		break;
	case eMoveDir::Up:
		velocity.y = -1.f;
		break;
	case eMoveDir::Down:
		velocity.y = 1.f;
		break;
	}

//	aAgent.SetVelocity(velocity);
}

void MoveCommand::Undo(Agent& aAgent)
{
}



