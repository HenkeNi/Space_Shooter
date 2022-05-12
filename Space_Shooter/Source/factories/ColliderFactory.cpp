#include "pch.h"
#include "ColliderFactory.h"
#include "BoxCollider.h"
#include "Dispatcher.h"
#include "Event.h"



BoxCollider* ColliderFactory::CreateBoxCollider(eCollisionLayer aLayer)
{
	BoxCollider* collider = new BoxCollider{ aLayer };
	return collider;
}

CircleCollider* ColliderFactory::CreateCircleCollider(eCollisionLayer aLayer)
{
	CircleCollider* collider = new CircleCollider{ aLayer };
	return collider;
}

LineCollider* ColliderFactory::CreateLineCollider(eCollisionLayer)
{
	return nullptr;
}