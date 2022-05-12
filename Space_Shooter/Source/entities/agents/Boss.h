 #pragma once
#include "BossState.h"
#include "Agent.h"



class Boss : public Agent
{
public:
	Boss(AgentData& someData);
	~Boss();

	virtual void Recieve(const Event& aEvent)		override;
	virtual void OnCollision(Entity& aEntity)		override;
	virtual void Update(float aDeltaTime)			override;
	virtual void TakeDamage(int aDamage)			override;
	virtual bool IsMarkedForRemoval()		  const override;


	void SetActiveState(BossState& aState);	
	bool IsSecondStageActive();
	

private:
	/* - Methods - */
	void Init();


	/* - Members - */
	BossState*									m_activeState;
};
