#pragma once
#include "Entity.h"

// TODO: Make enemy..?? or interactagble? -> circle Collider
class Asteroid  : public Entity
{
public:
	Asteroid(sf::Texture* aTexture);
	~Asteroid();

	virtual void				Recieve(const Event& aEvent)						  override;
	virtual void				OnCollision(Entity& another)						  override;
	virtual void				Update(float aDeltaTime)							  override;
	virtual bool				IsMarkedForRemoval()							const override;
	void						Init(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aVelocity);


private:
	/* - Methods - */
	void						UpdateMovement(float aDeltaTime);

	/* - Members - */
	CU::Vector2<float>			m_velocity;
	bool						m_isDestroyed;
};

