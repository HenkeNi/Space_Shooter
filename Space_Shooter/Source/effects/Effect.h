#pragma once
#include "Player.h"


class Effect
{
public:
	Effect(float aDuration) : m_duration{ aDuration }, m_timePassed{ 0 } {}
	
	virtual void	Activate(Player& aPlayer)	= 0;
	virtual bool	Update(float aDeltaTime)	= 0;
	virtual void	Deactive(Player& aPlayer)	= 0;

protected:
	float			m_duration;
	float			m_timePassed;
};