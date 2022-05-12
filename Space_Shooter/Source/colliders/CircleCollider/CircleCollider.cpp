#include "pch.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "Dispatcher.h"
#include "Event.h"
#include "LineCollider.h"
#include "Intersection.hpp"



CircleCollider::CircleCollider(eCollisionLayer aLayer)
	: CollisionObject{ aLayer }, m_offset{ 0.f, 0.f }, m_radius{ 0.f }
{
	Dispatcher::GetInstance().SendEvent(Event{ eEvent::CircleColliderCreated, this });
}

void CircleCollider::Init(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aCenter, float aRadius)
{
	m_position = aPosition;
	m_radius = aRadius; // NEEDED ??
	m_circle = { aCenter, aRadius };

	InitDebugCircle();
}

void CircleCollider::InitDebugCircle()
{
	m_debugShape.setOrigin({ m_position.x + m_radius, m_position.y + m_radius });
	m_debugShape.setPosition({ m_position.x, m_position.y }); // NEEDED?
	m_debugShape.setRadius(m_radius);
	m_debugShape.setFillColor(sf::Color::Transparent);
	m_debugShape.setOutlineThickness(2.f);
	m_debugShape.setOutlineColor(sf::Color::Green);
}

void CircleCollider::DrawDebug(sf::RenderTarget& aTarget)
{
	aTarget.draw(m_debugShape);
}
void CircleCollider::Update()
{
	// TODO: Add offset
	m_circle.InitWithCenterAndRadius(m_position, m_circle.GetRadius());
	m_debugShape.setPosition({ m_circle.GetCenterPosition().x, m_circle.GetCenterPosition().y });
}

bool CircleCollider::IsColliding(const CollisionObject& aCollisionObject)	const
{
	return aCollisionObject.IsColliding(*this);
}

bool CircleCollider::IsColliding(const BoxCollider& aBoxCollider)			const
{
	return CU::IntersectionAABB2DVsCircle(aBoxCollider.GetPrimitive(), m_circle);
}

bool CircleCollider::IsColliding(const CircleCollider& aCircleCollider)		const
{
	return CU::IntersectionCircleVsCircle(aCircleCollider.GetPrimitive(), m_circle);
}

bool CircleCollider::IsColliding(const LineCollider& aLineCollider)			const
{
	return CU::IntersectionLineVsCircle(aLineCollider.GetPrimitive(), m_circle);
}

const CU::Circle<float>& CircleCollider::GetPrimitive()						const
{
	return m_circle;
}

void CircleCollider::SetOffset(const CU::Vector2<float>& aOffset)
{
	m_offset = aOffset;
}