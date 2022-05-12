#pragma once

class Boss;

class BossState
{
public:
	virtual ~BossState() = default;

	virtual void Update(Boss* aBoss, float aDeltaTime)	= 0;
	virtual void Enter(Boss* aBoss)						= 0;
	virtual void Toggle(Boss* aBoss)					= 0;
	virtual void Exit(Boss* aBoss)						= 0;
};