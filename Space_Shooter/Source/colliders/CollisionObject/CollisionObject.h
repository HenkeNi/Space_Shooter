#pragma once
#include "eCollisionLayer.h"
#include "Vector.hpp"

class BoxCollider;
class CircleCollider;
class LineCollider;
class Entity;


namespace CU = CommonUtilities;

class CollisionObject
{
public:
	CollisionObject(eCollisionLayer aLayer);
	virtual ~CollisionObject();

	virtual void				Update()													  = 0;
	virtual void				DrawDebug(sf::RenderTarget& aTarget);
	
	virtual bool				IsColliding(const CollisionObject& aCollisionObject)	const = 0;
	virtual bool				IsColliding(const BoxCollider& aBoxCollider)			const = 0;
	virtual bool				IsColliding(const CircleCollider& aCircleCollider)		const = 0;
	virtual bool				IsColliding(const LineCollider& aLineCollider)			const = 0;

	const CU::Vector2<float>&	GetPosition()												const;
	eCollisionLayer				GetCollisionLayer()											const; 
	Entity*						GetOwner()													const;
	bool						CollidesWithLayer(eCollisionLayer aLayer) const;

	bool						AddCollisionLayer(eCollisionLayer aLayer);
	inline void						SetCollisionLayers(std::bitset<(int)eCollisionLayer::Count> aLayer)
	{
		m_layersToCollideWith2 = aLayer;
	}
	void						SetPosition(const CU::Vector2<float>& aPosition); 
	void						SetOwner(Entity* aOwner);

protected:
	CU::Vector2<float>			m_position;
	eCollisionLayer				m_collisionLayer;
	Entity*						m_owner;
	
	
	std::bitset<(int)eCollisionLayer::Count> m_layersToCollideWith2;
	std::set<eCollisionLayer>	m_layersToCollideWith; // replace with BTSSet or std::bitset<8>

	//std::bitset<8>				m_layersToCollideWith;
	// bool m_isActive;
};