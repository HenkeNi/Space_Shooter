#include "pch.h"
#include "AgentFactory.h"
#include "Boss.h"
#include "Dispatcher.h"
#include "Enemy.h"
#include "Player.h"


AgentFactory::AgentFactory(SharedContext aSharedContext, ColliderFactory& aColliderFactory)
	: m_sharedContext{ aSharedContext }, m_colliderFactory{ aColliderFactory }
{
}

void AgentFactory::Init()
{
	LoadAgentData();
	LoadWeaponData();
}

Boss* AgentFactory::CreateBoss(int aType)
{
	Boss* boss = new Boss{ m_agentData[aType] };

	/* - Add Collider - */
	CircleCollider* collider = m_colliderFactory.CreateCircleCollider(eCollisionLayer::Enemy);
	collider->Init({ 0, 0 }, { 0, 0 }, boss->GetSize().x * 0.5f); // Center AND Position??
	//auto* collider = m_colliderFactory.CreateBoxCollider(eCollisionLayer::Boss);
	//collider->Init({ 0, 0 }, boss->GetSize()); // Center AND Position??
	collider->AddCollisionLayer(eCollisionLayer::Player);
	collider->AddCollisionLayer(eCollisionLayer::PlayerBullet);
	boss->AddCollider(collider);
	
	for (int id : boss->GetAgentData().m_weaponIds)
	{
		boss->RegisterWeapon(CreateWeapon(static_cast<eWeaponType>(id), false));
	}
	
	Dispatcher::GetInstance().SendEvent({ eEvent::BossCreated, boss });
	return boss;
}

Enemy* AgentFactory::CreateEnemy(int aType)
{
	Enemy* enemy = new Enemy{ m_agentData[aType] };
	
	/* - Add Collider - */
	BoxCollider* collider = m_colliderFactory.CreateBoxCollider(eCollisionLayer::Enemy); // TODO: Put in ENemy constructor??
	collider->Init({ 0, 0 }, enemy->GetSize());
	collider->AddCollisionLayer(eCollisionLayer::Player);
	collider->AddCollisionLayer(eCollisionLayer::PlayerBullet);
	enemy->AddCollider(collider);

	for (int id : enemy->GetAgentData().m_weaponIds)
	{
		enemy->RegisterWeapon(CreateWeapon(static_cast<eWeaponType>(id), false));
	}

	Dispatcher::GetInstance().SendEvent({ eEvent::EnemyCreated, enemy });
	return enemy;
}

Player* AgentFactory::CreatePlayer(int aType)
{
	Player* player = new Player{ m_agentData[aType] };

	/* - Add Collider - */
	BoxCollider* collider = m_colliderFactory.CreateBoxCollider(eCollisionLayer::Player);
	collider->Init(player->GetPosition(), player->GetSize());
	collider->AddCollisionLayer(eCollisionLayer::Enemy);
	collider->AddCollisionLayer(eCollisionLayer::EnemyBullet);
	collider->AddCollisionLayer(eCollisionLayer::Pickup);
	collider->AddCollisionLayer(eCollisionLayer::Boss);
	player->AddCollider(collider);

	for (int id : player->GetAgentData().m_weaponIds)
	{
		player->RegisterWeapon(CreateWeapon(static_cast<eWeaponType>(id), true));
	}

	Dispatcher::GetInstance().SendEvent({ eEvent::PlayerCreated, player });
	return player;
}

void AgentFactory::LoadAgentData()
{
	std::ifstream ifs{ "Assets/Json/Agents.json" };
	std::string content{ std::istreambuf_iterator<char>(ifs), (std::istreambuf_iterator<char>()) };

	rapidjson::Document document;
	if (document.Parse(content.c_str()).HasParseError()) { std::cerr << "Error parsing \'Agents.json\'\n"; return; }

	for (auto& agent : document["agents"].GetArray())
	{
		AgentData data;
		data.m_size          = { agent["size"]["width"].GetFloat(), agent["size"]["height"].GetFloat() };
		data.m_movementSpeed = agent["movement_speed"].GetFloat();
		data.m_maxHealth	 = agent["max_health"].GetInt();

		for (auto& texture : agent["textures"].GetArray())
		{
			data.m_textures.push_back(&m_sharedContext.m_textures.GetResource(texture["identifier"].GetString()));
		}		

		for (auto& weapon : agent["weapons"].GetArray())
		{
			data.m_weaponIds.push_back(weapon["id"].GetInt());
		}
		m_agentData[agent["id"].GetInt()] = data;
	}
}

void AgentFactory::LoadWeaponData()
{
	std::ifstream ifs{ "Assets/Json/Weapons.json" };
	std::string content{ std::istreambuf_iterator<char>(ifs), (std::istreambuf_iterator<char>()) };

	rapidjson::Document	document;
	if (document.Parse(content.c_str()).HasParseError()) { std::cerr << "Error parsing \'Weapons.json\'!\n"; return; }

	for (auto& weapon : document["weapons"].GetArray())
	{
		WeaponData data;
		data.m_nextShotDelay = weapon["fire_rate"].GetFloat();
		data.m_bulletType	 = static_cast<eBulletType>(weapon["bullet_id"].GetInt());

		for (auto& direction : weapon["directions"].GetArray())
		{
			data.m_projectileDirections.push_back({ direction["x"].GetFloat(), direction["y"].GetFloat() });
		}

		int id = weapon["id"].GetInt();
		m_weaponData[id] = data;
	}
}

std::unique_ptr<Weapon> AgentFactory::CreateWeapon(eWeaponType aType, bool isPlayer)
{
	return std::make_unique<Weapon>(m_weaponData[static_cast<int>(aType)], isPlayer);
}