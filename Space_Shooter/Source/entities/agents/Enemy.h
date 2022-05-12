#pragma once
#include "Agent.h"
#include "Weapon.h"


class Enemy : public Agent
{
public:
	Enemy(AgentData& someData);
	~Enemy();

	virtual void Recieve(const Event& aEvent)	override;
	virtual void OnCollision(Entity& aEntity)	override;
	virtual void Update(float aDeltaTime)		override;
	virtual bool IsMarkedForRemoval()	  const override;

	void TakeDamage(int aDamage);

	

private:
	/* - Methods - */
	void FireWeapon();

	/* - Members - */
	

};