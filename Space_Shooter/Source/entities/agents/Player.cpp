#include "pch.h"
#include "Player.h"
#include "AgentData.h"
#include "Dispatcher.h"
#include "Weapon.h"
#include "CollisionObject.h"

#include "Bullet.h"
#include "Pickup.h"
#include "Effect.h"


Player::Player(AgentData& someData)
	: Agent{ someData }, m_isKnockedback{ false }, m_knockbackDelay{ 0.5f }, m_isInvulnerable{ false }, m_speedMultiplier{ 1 }
{
}

void Player::Recieve(const Event& aEvent)
{
	switch (aEvent.GetEventType())
	{
	case eEvent::EnemyDeath: // Level listen to ENemy death??
		break;
	}
}

void Player::OnCollision(Entity& aEntity)
{
	switch (aEntity.GetCollider()->GetCollisionLayer())
	{
	case eCollisionLayer::Enemy:
		Knockback({ -m_velocity.x, -m_velocity.y }); // Equal incoming velocity instead? - if 0.f, 0.f then use Enemy's... PROBLME: WHEN STANDING STILL..
		//Knockback(dynamic_cast<Agent&>(aEntity).GetVelocity()); // Equal incoming velocity instead?
		m_isKnockedback = true; // FIX
		m_knockbackTime = 0;
		--m_extraLives;
		break;
	case eCollisionLayer::EnemyBullet:
		TakeDamage(dynamic_cast<Bullet&>(aEntity).GetDamage());
		break;
	case eCollisionLayer::Pickup:
		AddEffect(dynamic_cast<Pickup&>(aEntity).GetEffect());
		break;
	}

	//if (aEntity.GetCollider()->GetCollisionLayer() == eCollisionLayer::Enemy)
	//{

	//	//--m_currentHealth;
	//	//m_knockbackTime = 0;
	//	//CU::Vector2<float> direction = aEntity.GetPosition() - m_position;
	//	
	//	//Knockback({ -m_velocity.x, -m_velocity.y }); // TODO: get position instead?? or will always collide 
	//}

}

void Player::Update(float aDeltaTime)
{
	Agent::Update(aDeltaTime);
	UpdateEffects(aDeltaTime);


	UpdateTexture();
	UpdatePreviousPosition();

	if (m_isKnockedback) // FIX....
	{
		m_knockbackTime += aDeltaTime;
	}
	if (m_knockbackTime >= m_knockbackDelay)
	{
		m_isKnockedback = false;
	}
}

void Player::TakeDamage(int aDamage)
{
	if (m_isInvulnerable || !IsAlive()) { return; }

	if ((m_currentHealth - aDamage) <= 0)
	{
		if ((--m_extraLives) < 0)
		{
			m_extraLives = 0;
			std::cout << "Player is dead!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
			Dispatcher::GetInstance().SendEvent(Event{ eEvent::PlayerDeath, true });
		}
		m_currentHealth = m_agentData.m_maxHealth;
		//m_currentHealth = 0; // TODO: LOse extra life?!
		//Dispatcher::GetInstance().SendEvent(Event{ eEvent::PlayerDeath, true });
	}
	else
	{
		Dispatcher::GetInstance().SendEvent(Event{ eEvent::PlayerHit, true });
	}
}

bool Player::IsMarkedForRemoval()	const
{
	return false;
}

void Player::Init(const CU::Vector2<float>& aSpawnPosition)
{
	m_spawnPosition = aSpawnPosition;
	SetPosition(aSpawnPosition);
	//m_position = aSpawnPosition;

	m_currentWeaponIndex = 0;

	m_extraLives = 3;

	// Init Collider..

	//m_activeWeapon = m_weapons[0].get();
}

void Player::HandleInput()
{
	bool isHandled = false;

	if (!m_isKnockedback)
	{
		/* https://www.youtube.com/watch?v=D2a5fHX-Qrs - 22:45 */
		// m_velocity = { 0.f, 0.f }; // TEST..

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_velocity.y = -m_speedMultiplier;
			isHandled = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_velocity.y = m_speedMultiplier;
			isHandled = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_velocity.x = -m_speedMultiplier;
			isHandled = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_velocity.x = m_speedMultiplier;
			isHandled = true;
		}

		if (!isHandled)
		{
			m_velocity = { 0.f, 0.f };
		}

		if (abs(m_velocity.x) > 0.f || abs(m_velocity.y) > 0.f)
		{
			m_velocity.Normalize();
			// Normalize and scale with speed..?!
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		m_weapons[m_currentWeaponIndex]->Shoot({ m_position.x, m_position.y - m_size.y * 0.5f});
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		ToggleWeapon();
}

void Player::SetSpeedMultiplier(int aMultiplier)
{
	m_speedMultiplier = aMultiplier;
}

void Player::AddEffect(Effect* aEffect)
{
	aEffect->Activate(*this);
	m_activeEffects.push_back(aEffect);
}

void Player::IncrementLives()
{
	++m_extraLives;
}

void Player::Respawn()
{
	SetPosition(m_spawnPosition);
	m_currentHealth = 3;
	m_currentWeaponIndex = 0;
	//m_activeWeapon = m_weapons[0].get();
}

//void Player::UpdateMovement(float aDeltaTime)
//{
//	m_position += m_velocity * m_agentData.m_movementSpeed * (float)m_speedMultiplier * aDeltaTime;
//	m_sprite.setPosition({ m_position.x, m_position.y });
//}

void Player::SetShieldActivation(bool aActivate)
{
	std::cout << "Activate shield\n";
	m_isInvulnerable = aActivate;

	// TODO: Sprite... Shield
}

void Player::ToggleWeapon()
{
	static sf::Clock swapTimer;
	if (swapTimer.getElapsedTime() > sf::seconds(0.25f))
	{
		if ((++m_currentWeaponIndex) >= m_weapons.size())
		{
			m_currentWeaponIndex = 0;
		 }
		swapTimer.restart();
	}
}

void Player::UpdateTexture()
{	
	int index = static_cast<int>(GetMovementDirection());
	if (index < m_agentData.m_textures.size() && m_agentData.m_textures[index] != nullptr)
	{
		m_sprite.setTexture(*m_agentData.m_textures[index]);
	}
}

void Player::UpdateEffects(float aDeltaTime)
{
	for (int i = 0; i < m_activeEffects.size(); ++i)
	{
		if (m_activeEffects[i]->Update(aDeltaTime))
		{
			m_activeEffects[i]->Deactive(*this);
			m_activeEffects.erase(m_activeEffects.begin() + i);
		}
	}
}
 


//void Aircraft::UpdateMovement(float aDeltaTime)
//{
//	m_sprite.move(m_velocity * m_movementSpeed * aDeltaTime);
//	std::cout << m_movementSpeed << '\n';
//	sf::Vector2f position = m_sprite.getPosition();
//	sf::FloatRect size = m_sprite.getLocalBounds();
//
//	// x-axis
//	if (position.x - (size.width * 0.5f) < 0.f)
//	{
//		m_sprite.setPosition({ size.width * 0.5f, position.y });
//	}
//	else if (position.x + (size.width * 0.5f) > 1024)
//	{
//		m_sprite.setPosition({ 1024 - (size.width * 0.5f), position.y });
//	}
//
//	// y-axis
//	if (position.y - (size.height * 0.5f) < 0.f)
//	{
//		m_sprite.setPosition({ position.x, size.width * 0.5f });
//	}
//	else if (position.y + (size.height * 0.5f) > 600) // half height
//	{
//		m_sprite.setPosition({ position.x, 600 - (size.height * 0.5f) });
//	}
//
//}