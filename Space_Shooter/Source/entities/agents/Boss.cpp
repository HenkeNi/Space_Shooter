#include "pch.h"
#include "Boss.h"
#include "Dispatcher.h"


Boss::Boss(AgentData& someData)
	: Agent{ someData }
{
	Init();
}

Boss::~Boss()
{
	//Dispatcher::GetInstance().SendEvent(Event{ eEvent::BossDeath, m_position });
}

void Boss::Recieve(const Event& aEvent)
{
}

void Boss::OnCollision(Entity& aEntity)
{
	std::cout << "Collided!\n";
}

void Boss::Update(float aDeltaTime)
{
	Agent::Update(aDeltaTime);
	
	/*if (m_activeState)
		m_activeState->Update(this, aDeltaTime);*/


	
}

void Boss::TakeDamage(int aDamage)
{
	if ((--m_currentHealth) < 0)
		m_currentHealth = 0;
}

bool Boss::IsMarkedForRemoval() const
{
	return false;
}

void Boss::SetActiveState(BossState& aState)
{
	m_activeState = &aState;
}

void Boss::Init()
{
	//m_shape.setSize({ 100.f, 100.f });
	//m_shape.setFillColor(sf::Color::Red);
	//m_shape.setPosition({ 500.f, 100.f });

	//m_shape.setOrigin({ m_shape.getSize().x * 0.5f, m_shape.getSize().y * 0.5f });

	m_velocity = { 0.f, 0.f };
}
//
//void Boss::UpdateMovement(float aDeltaTime)
//{
//	m_sprite.move(m_velocity * m_enemyData.GetMovementSpeed() * aDeltaTime);
//
//	auto position = m_sprite.getPosition();
//	auto size = m_sprite.getLocalBounds();
//
//	// x-axis
//	if (position.x - (size.width * 0.5f) < 0.f)
//	{
//		m_sprite.setPosition({ size.width * 0.5f, position.y });
//	}
//	else if (position.x + (size.width * 0.5f) > 1024)
//	{
//		m_sprite.setPosition({ 1024 - (size.width * 0.5f), position.y });
//	}
//
//	// y-axis
//	if (position.y - (size.height * 0.5f) < 0.f)
//	{
//		m_sprite.setPosition({ position.x, size.width * 0.5f });
//	}
//	else if (position.y + (size.height * 0.5f) > 300) // half height
//	{
//		m_sprite.setPosition({ position.x, 300 - (size.height * 0.5f) });
//	}
//}
//




bool Boss::IsSecondStageActive()
{ 
	return false;
}

