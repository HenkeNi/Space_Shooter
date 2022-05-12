#pragma once
#include "CollisionObject.h"
#include "Circle.hpp"


class CircleCollider : public CollisionObject
{
public:
	CircleCollider(eCollisionLayer aLayer);

	void						Init(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aCenter, float aRadius);
	void						InitDebugCircle();
	virtual void				DrawDebug(sf::RenderTarget& aTarget)						  override;
	virtual void				Update()													  override;

	virtual bool				IsColliding(const CollisionObject& aCollisionObject)	const override;
	virtual bool				IsColliding(const BoxCollider& aBoxCollider)			const override;
	virtual bool				IsColliding(const CircleCollider& aCircleCollider)		const override;
	virtual bool				IsColliding(const LineCollider& aLineCollider)			const override;
	
	const CU::Circle<float>&	GetPrimitive()													 const;
	void						SetOffset(const CU::Vector2<float>& aOffset);

private:
	CU::Circle<float>			m_circle;
	CU::Vector2<float>			m_offset;
	sf::CircleShape				m_debugShape;
	float						m_radius; // TODO: NEEDED?
};

