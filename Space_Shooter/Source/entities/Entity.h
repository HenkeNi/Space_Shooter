#pragma once
#include "Subscriber.h"
#include "Vector.hpp"

namespace CU = CommonUtilities;


class CollisionObject;

class Entity : public Subscriber
{
public:
	Entity(const sf::Texture& aTexture);
	virtual ~Entity();

	virtual void				Update(float aDeltaTime)								   = 0;
	virtual void				OnCollision(Entity& aEntity)							   = 0;
	virtual bool				IsMarkedForRemoval()								 const = 0;
	virtual bool				IsOutOfBounds(const CU::Vector2<unsigned>& aSize)	 const;
	
	void						Render(sf::RenderTarget& aTarget)					 const;
	unsigned					GetId()												 const;
	const CU::Vector2<float>&	GetPosition()										 const;
	const CU::Vector2<float>&	GetSize()											 const;
	const CollisionObject*		GetCollider()										 const;
	
	void						AddCollider(CollisionObject* aCollisionObject);
	void						SetPosition(const CU::Vector2<float>& aPosition);

protected:
	/* - Methods - */
	unsigned					GenerateId()										 const;
	void						UpdateCollider();

	/* - Members - */
	sf::Sprite					m_sprite;
	CU::Vector2<float>			m_position;
	CU::Vector2<float>			m_size;
	unsigned int				m_id;
	CollisionObject*			m_collisionObject;
};