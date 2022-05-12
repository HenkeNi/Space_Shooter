#include "pch.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Dispatcher.h"
#include "Event.h"
#include "Intersection.hpp"
#include "LineCollider.h"


BoxCollider::BoxCollider(eCollisionLayer aLayer)
	: CollisionObject{ aLayer }, m_offset{ 0.f, 0.f }
{
	Dispatcher::GetInstance().SendEvent(Event{ eEvent::BoxColliderCreated, this });
}

void BoxCollider::Init(const CU::Vector2<float>& aMinPoints, const CU::Vector2<float>& aMaxPoints)
{
	m_AABB.InitWithMinAndMax(aMinPoints, aMaxPoints);
	InitDebugRect();
}

void BoxCollider::InitDebugRect()
{
	float width = m_AABB.GetMaxPoint().x - m_AABB.GetMinPoint().x;
	float height = m_AABB.GetMaxPoint().y - m_AABB.GetMinPoint().y;

	m_debugRect.setOrigin(width * 0.5f, height * 0.5f); // TODO: Include offset!?
	m_debugRect.setSize({ width, height });
	m_debugRect.setFillColor(sf::Color::Transparent); // default?
	m_debugRect.setOutlineThickness(2.f);
	m_debugRect.setOutlineColor(sf::Color::Green);
}

void BoxCollider::DrawDebug(sf::RenderTarget& aTarget)
{
	aTarget.draw(m_debugRect);
}

void BoxCollider::Update()
{
	float width  = m_AABB.GetMaxPoint().x - m_AABB.GetMinPoint().x;
	float height = m_AABB.GetMaxPoint().y - m_AABB.GetMinPoint().y;

	auto offsetPosition = m_position + m_offset;

	m_AABB.InitWithMinAndMax({ offsetPosition.x - (width * 0.5f), offsetPosition.y - (height * 0.5f) },
		{ offsetPosition.x + (width * 0.5f), offsetPosition.y + (height * 0.5f) });

	m_debugRect.setPosition({ offsetPosition.x, offsetPosition.y });
}

bool BoxCollider::IsColliding(const CollisionObject& aCollisionObject)	const 
{
	return aCollisionObject.IsColliding(*this);
}

bool BoxCollider::IsColliding(const BoxCollider& aBoxCollider)			const
{
	return CU::IntersectionAABB2DVsAABB2D(m_AABB, aBoxCollider.m_AABB);
}

bool BoxCollider::IsColliding(const CircleCollider& aCircleCollider)	const
{
	return CU::IntersectionAABB2DVsCircle(m_AABB, aCircleCollider.GetPrimitive());
} 

bool BoxCollider::IsColliding(const LineCollider& aLineCollider)		const
{
	return CU::IntersectionAABB2DVsLine(m_AABB, aLineCollider.GetPrimitive());
}

const CU::AABB2D<float>& BoxCollider::GetPrimitive()					const
{
	return m_AABB;
}

void BoxCollider::SetOffset(const CU::Vector2<float>& aOffset)
{
	m_offset = aOffset;
}