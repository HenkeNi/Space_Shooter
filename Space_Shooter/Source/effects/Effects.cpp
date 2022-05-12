#include "pch.h"
#include "Effects.h"



/************************** Speed Boost **************************/
#pragma region SPEED_BOOST
SpeedBoost::SpeedBoost(float aDuration)
	: Effect{ aDuration }
{
}

void SpeedBoost::Activate(Player& aPlayer)
{
	aPlayer.SetSpeedMultiplier(2);
}

bool SpeedBoost::Update(float aDeltaTime) // TODO: Put in Effect??
{
	m_timePassed += aDeltaTime;
	return m_timePassed >= m_duration;
}

void SpeedBoost::Deactive(Player& aPlayer)
{
	aPlayer.SetSpeedMultiplier(1);
}
#pragma endregion



/************************** Shield Boost **************************/
#pragma region SHIELD_BOOST
ShieldBoost::ShieldBoost(float aDuration)
	: Effect{ aDuration }
{
}

void ShieldBoost::Activate(Player& aPlayer)
{
	aPlayer.SetShieldActivation(true);
}

bool ShieldBoost::Update(float aDeltaTime)
{
	m_timePassed += aDeltaTime;
	return m_timePassed >= m_duration;
}

void ShieldBoost::Deactive(Player& aPlayer)
{
	aPlayer.SetShieldActivation(false);
}
#pragma endregion



/************************** Health Boost **************************/
#pragma region HEALTH_BOOST
HealthBoost::HealthBoost(float aDuration)
	: Effect{ aDuration }
{
}

void HealthBoost::Activate(Player& aPlayer)
{
	aPlayer.IncrementLives();
}

bool HealthBoost::Update(float aDeltaTime)
{
	m_timePassed += aDeltaTime;
	return m_timePassed >= m_duration;
}

void HealthBoost::Deactive(Player& aPlayer)
{
}
#pragma endregion