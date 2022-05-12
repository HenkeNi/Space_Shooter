#include "pch.h"
#include "BulletFactory.h"
#include "Bullet.h"
#include "ColliderFactory.h"
#include "Dispatcher.h"


BulletFactory::BulletFactory(SharedContext aSharedContext, ColliderFactory& aColliderFactory)
	: m_sharedContext{ aSharedContext }, m_colliderFactory{ aColliderFactory }
{
}

void BulletFactory::Init()
{
	LoadBulletData();
}

Bullet* BulletFactory::CreatePlayerBullet(int aType)
{
	Bullet* bullet = new Bullet{ m_bulletData[static_cast<int>(aType)] };
	
	/* - Add Collider - */
	auto* collider = m_colliderFactory.CreateBoxCollider(eCollisionLayer::PlayerBullet);
	collider->Init(bullet->GetPosition(), bullet->GetSize());
	collider->AddCollisionLayer(eCollisionLayer::Enemy);
	bullet->AddCollider(collider);

	Dispatcher::GetInstance().SendEvent(Event{ eEvent::BulletCreated, bullet });
	return bullet;
}

Bullet* BulletFactory::CreateEnemyBullet(int aType)
{
	Bullet* bullet = new Bullet{ m_bulletData[static_cast<int>(aType)] };

	/* - Add Collider - */
	auto* collider = m_colliderFactory.CreateBoxCollider(eCollisionLayer::EnemyBullet);
	collider->Init(bullet->GetPosition(), bullet->GetSize());
	collider->AddCollisionLayer(eCollisionLayer::Player);
	bullet->AddCollider(collider);

	Dispatcher::GetInstance().SendEvent(Event{ eEvent::BulletCreated, bullet }); // TODO: move to constructor..?
	return bullet;
}

void BulletFactory::LoadBulletData()
{
	std::ifstream ifs{ "Assets/Json/Bullets.json" };
	std::string	  content{ std::istreambuf_iterator<char>(ifs), (std::istreambuf_iterator<char>()) };

	rapidjson::Document document;
	if (document.Parse(content.c_str()).HasParseError()) { std::cerr << "Error parsing \'BulletData.json\'!\n"; return; }

	for (auto& bullet : document["bullets"].GetArray())
	{
		BulletData data;
		data.m_size    = { bullet["size"]["width"].GetFloat(), bullet["size"]["height"].GetFloat() };
		data.m_speed   = bullet["speed"].GetFloat();
		data.m_damage  = bullet["damage"].GetInt();
		data.m_texture = &m_sharedContext.m_textures.GetResource(bullet["texture"].GetString());

		m_bulletData[bullet["id"].GetInt()] = data;
	}
}