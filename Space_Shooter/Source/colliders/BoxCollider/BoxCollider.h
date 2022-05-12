#pragma once
#include "AABB2D.hpp"
#include "CollisionObject.h"


class BoxCollider : public CollisionObject
{
public:
	BoxCollider(eCollisionLayer aLayer);

	void						Init(const CU::Vector2<float>& aMinPoints, const CU::Vector2<float>& aMaxPoints);
	void						InitDebugRect();
	virtual void				DrawDebug(sf::RenderTarget& aTarget)						  override;
	virtual void				Update()													  override;

	virtual bool				IsColliding(const CollisionObject& aCollisionObject)	const override;
	virtual bool				IsColliding(const BoxCollider& aBoxCollider)			const override;
	virtual bool				IsColliding(const CircleCollider& aCircleCollider)		const override;
	virtual bool				IsColliding(const LineCollider& aLineCollider)			const override;

	const CU::AABB2D<float>&	GetPrimitive()													 const;
	void						SetOffset(const CU::Vector2<float>& aOffset);

private:
	CU::AABB2D<float>			m_AABB;
	CU::Vector2<float>			m_offset; 
	sf::RectangleShape			m_debugRect;
};