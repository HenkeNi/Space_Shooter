#pragma once
#include "CollisionObject.h"
#include "Line.hpp"



class LineCollider : public CollisionObject
{
public:
	LineCollider(eCollisionLayer aLayer);

	void					Init(const CU::Vector2<float>& aPoint, const CU::Vector2<float>& aDirection);
	virtual void			Update()													  override;

	virtual bool			IsColliding(const CollisionObject& aCollisionObject)	const override;
	virtual bool			IsColliding(const BoxCollider& aBoxCollider)			const override;
	virtual bool			IsColliding(const CircleCollider& aCircleCollider)		const override;
	virtual bool			IsColliding(const LineCollider& aLineCollider)			const override;
	
	const CU::Line<float>&	GetPrimitive()													 const;

private:
	CU::Line<float>			m_line;
};

