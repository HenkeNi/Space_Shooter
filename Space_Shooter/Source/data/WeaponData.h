#pragma once
#include "eBulletType.h"
#include "Vector.hpp"

namespace CU = CommonUtilities;

struct WeaponData
{
	std::vector<CU::Vector2<float>>			m_projectileDirections;
	float									m_nextShotDelay;
	eBulletType								m_bulletType;
};

