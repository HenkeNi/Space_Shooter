#pragma once
#include "AgentData.h"
#include "eMoveDir.h"
#include "Entity.h"
#include "Weapon.h"



class Agent : public Entity
{
public:
	using Weapons_t = std::vector<std::unique_ptr<Weapon>>;

public:
	Agent(AgentData& someData);

	virtual void		TakeDamage(int aDamage)			      = 0;
	virtual void		Update(float aDeltaTime)		 override;
	void				Respawn();
	void				RegisterWeapon(std::unique_ptr<Weapon> aWeapon);
	void				SetVelocity(const CU::Vector2<float>& aVelocity);
	bool				IsAlive()												const;
	const AgentData&	GetAgentData()											const;
	const CU::Vector2<float>& GetVelocity()										const;

protected:
	/* -	Methods		- */
	void				UpdateMovement(float aDeltaTime);
	void				UpdatePreviousPosition();
	void				Knockback(const CU::Vector2<float>& aVelocity);
	eMoveDir			GetMovementDirection()									const;

	/* -	Members		- */
	Weapons_t			m_weapons;
	CU::Vector2<float>	m_previousPosition;
	CU::Vector2<float>	m_velocity;
	int					m_currentHealth;
	AgentData&			m_agentData;
};