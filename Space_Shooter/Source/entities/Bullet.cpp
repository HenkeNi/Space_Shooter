#include "pch.h"
#include "Bullet.h"
#include "Dispatcher.h"



Bullet::Bullet(BulletData& someData)
	: Entity{ *someData.m_texture }, m_bulletData{ someData }, m_isDestroyed{ false }
{
	//Dispatcher::GetInstance().SendEvent(Event{ eEvent::BulletCreated, this });
}

Bullet::~Bullet()
{
}

void Bullet::Recieve(const Event& aEvent)
{
}

void Bullet::OnCollision(Entity& another)
{
	std::cout << "Bullet collision\n";
	m_isDestroyed = true;
}

void Bullet::Update(float aDeltaTime)
{
	// TODO: Put in entity??
	UpdateMovement(aDeltaTime);
	UpdateCollider(); 
}

bool Bullet::IsMarkedForRemoval() const
{
	return m_isDestroyed;
}

void Bullet::Init(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aVelocity)
{
	m_sprite.setPosition({ aPosition.x, aPosition.y });
	m_velocity = aVelocity;
}

int Bullet::GetDamage() const
{
	return m_bulletData.m_damage;
}

const CU::Vector2<float>& Bullet::GetPosition() const
{
	//auto pos = m_sprite.getPosition();
	return { m_sprite.getPosition().x, m_sprite.getPosition().y };
}

void Bullet::SetVelocity(const CU::Vector2<float>& aVelocity)
{
	m_velocity = aVelocity;
}

void Bullet::UpdateMovement(float aDeltaTime)
{
	m_position += m_velocity * m_bulletData.m_speed * aDeltaTime;
	m_sprite.setPosition({ m_position.x, m_position.y });
}