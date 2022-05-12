#pragma once
#include "Entity.h"
#include "PickupData.h"


class Pickup : public Entity
{
public:
	Pickup(PickupData& someData);
	~Pickup();

	virtual void		Recieve(const Event& aEvent)	override;
	virtual void		OnCollision(Entity& aEntity)	override;
	virtual void		Update(float aDeltaTime)		override;
	virtual bool		IsMarkedForRemoval()	  const override;

	Effect*				GetEffect()						   const;

private:
	/* - Methods - */
	void				UpdateMovement(float aDeltaTime);

	/* - Members - */
	CU::Vector2<float>	m_velocity;
	bool				m_isCollected;
	PickupData&			m_pickupData;
};

