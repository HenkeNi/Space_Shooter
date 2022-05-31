#pragma once
#include "Entity.h"
#include "ObstacleData.h"

class BlackHole : public Entity
{
public:
	BlackHole(ObstacleData& someData);
	~BlackHole();

	virtual void				Recieve(const Event& aEvent)						  override;
	virtual void				OnCollision(Entity& another)						  override;
	virtual void				Update(float aDeltaTime)							  override;
	virtual bool				IsMarkedForRemoval()							const override;
	void						Init(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aVelocity);

private:
	/* - Methods - */
	void						UpdateMovement(float aDeltaTime);
	void						Attract();
	void						HandleOutOfRange();
	void						ResetPlayerPosition(Entity* aPlayer); // NEEDED?? Or have a default spawn position instead...?

	/* - Members - */
	CU::Vector2<float>			m_velocity;
	bool						m_isDestroyed; // REmove...
	std::vector<Entity*>		m_attractedEntities;
	
	ObstacleData&				m_obstacleData;

	CU::Vector2<float>			m_playerPosition;

	// PUT IN JSON:
	float m_gravitationalPull;
	float m_radiusOfNoReturn; 

	float m_deathRadius;

	
};

