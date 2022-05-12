#pragma once
#include "eCollisionLayer.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "LineCollider.h"


class ColliderFactory
{
public:
	ColliderFactory() = default;

	BoxCollider*		CreateBoxCollider(eCollisionLayer	 aLayer);
	CircleCollider*		CreateCircleCollider(eCollisionLayer aLayer);
	LineCollider*		CreateLineCollider(eCollisionLayer	 aLayer);
};

