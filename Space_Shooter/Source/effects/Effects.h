#pragma once
#include "Effect.h"

// Knockback...??

/************************** Speed Boost **************************/
class SpeedBoost : public Effect
{
public:
	SpeedBoost(float aDuration);

	virtual void Activate(Player& aPlayer)	override;
	virtual bool Update(float aDeltaTime)	override;
	virtual void Deactive(Player& aPlayer)	override;
};


/************************** Shield Boost **************************/
class ShieldBoost : public Effect
{
public:
	ShieldBoost(float aDuration);

	virtual void Activate(Player& aPlayer)	override;
	virtual bool Update(float aDeltaTime)	override;
	virtual void Deactive(Player& aPlayer)	override;
};


/************************** Health Boost **************************/
class HealthBoost : public Effect
{
public:
	HealthBoost(float aDuration);

	virtual void Activate(Player& aPlayer)	override;
	virtual bool Update(float aDeltaTime)	override;
	virtual void Deactive(Player& aPlayer)	override;
};