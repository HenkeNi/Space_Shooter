#include "pch.h"
#include "LineCollider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Intersection.hpp"



LineCollider::LineCollider(eCollisionLayer aLayer)
	: CollisionObject{ aLayer }
{
}

void LineCollider::Init(const CU::Vector2<float>& aPoint, const CU::Vector2<float>& aDirection)
{
	m_position = aPoint;
	m_line = { aPoint, aDirection };
}

void LineCollider::Update()
{

}

bool LineCollider::IsColliding(const CollisionObject& aCollisionObject)	const
{
	return aCollisionObject.IsColliding(*this);
}

bool LineCollider::IsColliding(const BoxCollider& aBoxCollider)			const
{
	return CU::IntersectionAABB2DVsLine(aBoxCollider.GetPrimitive(), m_line);
}

bool LineCollider::IsColliding(const CircleCollider& aCircleCollider)	const
{
	return CU::IntersectionLineVsCircle(m_line, aCircleCollider.GetPrimitive());
}

bool LineCollider::IsColliding(const LineCollider& aLineCollider)		const
{
	return CU::IntersectionLineVsLine(m_line, aLineCollider.GetPrimitive());
}

const CU::Line<float>& LineCollider::GetPrimitive()						const
{
	return m_line;
}