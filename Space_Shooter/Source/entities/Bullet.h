#pragma once
#include "BulletData.h"
#include "Entity.h"


class Bullet : public Entity
{
public:
	Bullet(BulletData& someData); 
	~Bullet();

	virtual void				Recieve(const Event& aEvent)						  override;
	virtual void				OnCollision(Entity& another)						  override;
	virtual void				Update(float aDeltaTime)							  override;
	virtual bool				IsMarkedForRemoval()							const override;
	void						Init(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aVelocity);

	int							GetDamage()												 const;
	const CU::Vector2<float>&	GetPosition()											 const; // NEEDED???
	void						SetVelocity(const CU::Vector2<float>& aVelocity);

private:
	/* - Methods - */
	void						UpdateMovement(float aDeltaTime);

	/* - Members - */
	CU::Vector2<float>			m_velocity;
	BulletData&					m_bulletData;
	bool						m_isDestroyed;
};

