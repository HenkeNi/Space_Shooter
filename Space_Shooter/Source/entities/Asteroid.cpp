#include "pch.h"
#include "Asteroid.h"


Asteroid::Asteroid(sf::Texture* aTexture)
	: Entity{ *aTexture }, m_isDestroyed{ false }
{
}

Asteroid::~Asteroid()
{
}

void Asteroid::Recieve(const Event& aEvent)						  
{
}

void Asteroid::OnCollision(Entity& another)						  
{
}

void Asteroid::Update(float aDeltaTime)							  
{
	UpdateMovement(aDeltaTime);
	UpdateCollider();
}

bool Asteroid::IsMarkedForRemoval()							const 
{
	return false;
}

void Asteroid::Init(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aVelocity)
{
	m_sprite.setPosition({ aPosition.x, aPosition.y });
	m_velocity = aVelocity;
}

void Asteroid::UpdateMovement(float aDeltaTime)
{
	m_position += m_velocity * aDeltaTime;
	m_sprite.setPosition({ m_position.x, m_position.y });
}