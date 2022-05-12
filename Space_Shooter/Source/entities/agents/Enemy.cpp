#include "pch.h"
#include "Enemy.h"
#include "Bullet.h"
#include "CollisionObject.h"
#include "Dispatcher.h"



Enemy::Enemy(AgentData& someData)
	: Agent{ someData }
{
}

Enemy::~Enemy()
{
	Dispatcher::GetInstance().SendEvent(Event{ eEvent::EnemyDeath, m_position });
}

void Enemy::Recieve(const Event& aEvent)
{

}

void Enemy::OnCollision(Entity& aEntity)
{
	if (aEntity.GetCollider()->GetCollisionLayer() == eCollisionLayer::PlayerBullet)
	{
		auto& bullet = dynamic_cast<Bullet&>(aEntity);
		TakeDamage(bullet.GetDamage());
	}
	if (aEntity.GetCollider()->GetCollisionLayer() == eCollisionLayer::Player)
	{
		m_currentHealth = 0;
	}
}

void Enemy::Update(float aDeltaTime)
{
	Agent::Update(aDeltaTime);
	FireWeapon();
}

bool Enemy::IsMarkedForRemoval() const
{
	return !IsAlive();
}

void Enemy::TakeDamage(int aDamage)
{
	if ((m_currentHealth -= aDamage) < 0)
	{
		m_currentHealth = 0;
	}
}

void Enemy::FireWeapon()
{
	m_weapons[0]->Shoot(GetPosition());  
}


