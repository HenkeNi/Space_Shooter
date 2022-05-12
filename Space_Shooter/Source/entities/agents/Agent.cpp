#include "pch.h"
#include "Agent.h"
#include "CollisionObject.h"



Agent::Agent(AgentData& someData)
	: Entity{ *someData.m_textures[0] }, m_agentData{ someData }, m_currentHealth{ someData.m_maxHealth }
{
}

void Agent::Update(float aDeltaTime)
{
	UpdateMovement(aDeltaTime);
	UpdateCollider();
}

void Agent::Respawn()
{
	m_currentHealth = m_agentData.m_maxHealth;
}

void Agent::RegisterWeapon(std::unique_ptr<Weapon> aWeapon)
{
	m_weapons.push_back(std::move(aWeapon));
}

void Agent::SetVelocity(const CU::Vector2<float>& aVelocity)
{
	m_velocity = aVelocity;
}

bool Agent::IsAlive() const
{
	return m_currentHealth > 0;
}

const AgentData& Agent::GetAgentData() const
{
	return m_agentData;
}

const CU::Vector2<float>& Agent::GetVelocity() const
{
	return m_velocity;
}

void Agent::UpdateMovement(float aDeltaTime)
{
	m_position += m_velocity * m_agentData.m_movementSpeed * aDeltaTime;
	m_sprite.setPosition({ m_position.x, m_position.y });
}

void Agent::UpdatePreviousPosition()
{
	m_previousPosition = m_position;
}

void Agent::Knockback(const CU::Vector2<float>& aVelocity) // TODO: have just in player?
{
	//static float force = 20.f;
	//m_velocity = aVelocity * force;
	m_velocity = aVelocity;
}

eMoveDir Agent::GetMovementDirection()	  const
{
	const auto& currentPos = GetPosition();

	if (m_previousPosition.x < currentPos.x)
		return eMoveDir::Right;
	if (m_previousPosition.x > currentPos.x)
		return eMoveDir::Left;
	if (m_previousPosition.y < currentPos.y)
		return eMoveDir::Down;
	if (m_previousPosition.y > currentPos.y)
		return eMoveDir::Up;

	return eMoveDir::Idle;
}