#include "pch.h"
#include "Entity.h"
#include "CollisionObject.h"


Entity::Entity(const sf::Texture& aTexture)
	: m_sprite{ aTexture }, m_id{ GenerateId() }, m_collisionObject{ nullptr }, m_size{ m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height }
{
	m_sprite.setOrigin(m_size.x * 0.5f, m_size.y * 0.5f);
}

Entity::~Entity()
{
	if (m_collisionObject)
	{
		delete m_collisionObject;
	}
}

bool Entity::IsOutOfBounds(const CU::Vector2<unsigned>& aSize) const
{
	return m_position.x + m_size.x < 0 || m_position.y + m_size.y < 0 
		|| m_position.x - m_size.x > aSize.x || m_position.y - m_size.y > aSize.y;
}

void Entity::Render(sf::RenderTarget& aTarget) const
{
	aTarget.draw(m_sprite);

	if (m_collisionObject && !IsMarkedForRemoval()) 
		m_collisionObject->DrawDebug(aTarget);
}

unsigned Entity::GetId() const
{
	return m_id;
}

const CU::Vector2<float>& Entity::GetPosition() const
{
	return m_position;
}

const CU::Vector2<float>& Entity::GetSize()		const
{
	return m_size;
}

const CollisionObject* Entity::GetCollider()	const
{
	return m_collisionObject;
}

void Entity::AddCollider(CollisionObject* aCollisionObject)
{
	m_collisionObject = aCollisionObject;
	m_collisionObject->SetOwner(this);
}

void Entity::SetPosition(const CU::Vector2<float>& aPosition)
{
	m_position = aPosition;
}

unsigned Entity::GenerateId()					const
{
	static int currentId = 1;
	return currentId++;
}

void Entity::UpdateCollider()
{
	if (m_collisionObject)
	{
		m_collisionObject->SetPosition(m_position);
		m_collisionObject->Update();
	}
}