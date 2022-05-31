#include "pch.h"
#include "BlackHole.h"
#include "CollisionObject.h"
#include "Dispatcher.h"


BlackHole::BlackHole(ObstacleData& someData)
	: Entity{ *someData.m_texture }, m_obstacleData{ someData }, m_isDestroyed{ false }, m_radiusOfNoReturn{ m_size.x * 1.75f }, m_deathRadius{ m_size.x * 1.f }
{
	Dispatcher::GetInstance().SendEvent(Event{ eEvent::BlackHoleCreated, this });
	SetVelocity({ 0.f, 1.f });
}

BlackHole::~BlackHole()
{
}

void BlackHole::Recieve(const Event& aEvent)
{
}

void BlackHole::OnCollision(Entity& another)
{
	if (std::find(m_attractedEntities.begin(), m_attractedEntities.end(), &another) == m_attractedEntities.end())
	{
		m_attractedEntities.push_back(&another);

		if (another.GetCollider()->GetCollisionLayer() == eCollisionLayer::Player)
		{
			m_playerPosition = another.GetPosition();
		}
	}
}

void BlackHole::Update(float aDeltaTime)
{
	UpdateMovement(aDeltaTime);
	UpdateCollider();

	Attract();
}

bool BlackHole::IsMarkedForRemoval() const
{
	return false;
}

void BlackHole::Init(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aVelocity)
{
	m_sprite.setPosition({ aPosition.x, aPosition.y });
	m_velocity = aVelocity;
}

void BlackHole::UpdateMovement(float aDeltaTime)
{
	m_position += m_velocity * aDeltaTime;
	m_sprite.setPosition({ m_position.x, m_position.y });
}

void BlackHole::Attract()
{
	for (auto& entity : m_attractedEntities)
	{
		static float gravitationalForce = 0.1f; // Multply with distance from hole?

		auto direction = m_position - entity->GetPosition();
		entity->SetVelocity(direction.GetNormalized() * gravitationalForce);
		
		if (direction.Length() < m_radiusOfNoReturn)
		{
			std::cout << "Disable player movement...\n";
		}

		if (direction.Length() < m_deathRadius) // Fix...
		{
			std::cout << "Kill....\n";
			if (entity->GetCollider()->GetCollisionLayer() == eCollisionLayer::Player)
			{
				ResetPlayerPosition(entity);
			}
		}
	}
}

void BlackHole::HandleOutOfRange()
{
	// When player escapes...
}

void BlackHole::ResetPlayerPosition(Entity* aPlayer)
{
	// player.setSpawnPosition()??

	auto direction = m_playerPosition - aPlayer->GetPosition();
	float length = direction.Length();
	
	direction.Normalize();

	auto pos = aPlayer->GetPosition();
	aPlayer->SetPosition({ pos.x + (direction.x * length), pos.y + (direction.y * length) });
}
