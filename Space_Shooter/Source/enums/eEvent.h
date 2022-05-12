#pragma once

enum class eEvent
{
	BoxColliderCreated/*, ColliderCreated*/, CircleColliderCreated, ColliderDestroyed, BossCreated, BulletCreated, EnemyCreated, PlayerCreated, PickupCreated,
	PlayerDeath, EnemyDeath,
	PlayerFire, EnemyFire,
	PlayerHit,
	LevelCompleted,
	Count
};