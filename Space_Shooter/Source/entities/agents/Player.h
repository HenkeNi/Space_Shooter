#pragma once
#include "Agent.h"
#include "eWeaponType.h"
#include "Vector.hpp"

namespace CU = CommonUtilities;

class Effect;
class Weapon;

class Player : public Agent
{
public:
	Player(AgentData& someData);

	virtual void	Recieve(const Event& aEvent)	override;
	virtual void	OnCollision(Entity& aEntity)	override;
	virtual void	Update(float aDeltaTime)		override;
	virtual void	TakeDamage(int aDamage)			override;
	virtual bool	IsMarkedForRemoval()	  const override;

	void			Init(const CU::Vector2<float>& aSpawnPosition);
	void			Respawn(); // COmbine init and respawn..? 
	
	void			HandleInput();

	void			SetSpeedMultiplier(int aMultiplier);


	void			SetShieldActivation(bool aActivate);
	void AddEffect(Effect* aEffect);
	void IncrementLives(); // RENAME?


	int GetLives() const
	{
		return m_extraLives;
	}

	int GetPoints() const
	{
		return m_points;
	}


private:
	/* - Methods - */
	void			ToggleWeapon();
	void			UpdateTexture(); // TODO: put in Agent?
	void			UpdateEffects(float aDeltaTime);


	/* - Members - */	
	CU::Vector2<float>		m_spawnPosition; 
	std::vector<Effect*>	m_activeEffects;
	int						m_speedMultiplier;
	int						m_extraLives;
	int						m_currentWeaponIndex; // Pointer to Weapon instead?
	int						m_currentTextureIndex;
	bool					m_isInvulnerable;


	bool					m_isKnockedback; // Make Effect instead?
	float					m_knockbackTime;
	float					m_knockbackDelay;


	int m_points = 0; // Make score manager or something??
};