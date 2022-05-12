#include "pch.h"
#include "PickupFactory.h"
#include "ColliderFactory.h"
#include "Dispatcher.h"
#include "Player.h"
#include "Pickup.h"
#include "Effects.h"


PickupFactory::PickupFactory(SharedContext aSharedContext, ColliderFactory& aColliderFactory)
	: m_sharedContext{ aSharedContext }, m_colliderFactory{ aColliderFactory }
{
}

PickupFactory::~PickupFactory()
{
	for (auto effect : m_effects)
		delete effect;
}

void PickupFactory::Init()
{
	InitEffects();
	LoadPickupData();
}

Pickup* PickupFactory::CreatePickup(int aType)
{
	Pickup* pickup = new Pickup{ m_pickupData[static_cast<int>(aType)] };
	
	/* - Add Collider - */
	auto* collider = m_colliderFactory.CreateBoxCollider(eCollisionLayer::Pickup);
	collider->Init(pickup->GetPosition(), pickup->GetSize());
	collider->AddCollisionLayer(eCollisionLayer::Player);
	pickup->AddCollider(collider);
	
	return pickup;
}

void PickupFactory::LoadPickupData()
{
	std::ifstream ifs{ "Assets/Json/Pickups.json" };
	std::string	  content{ std::istreambuf_iterator<char>(ifs), (std::istreambuf_iterator<char>()) };

	rapidjson::Document document;
	if (document.Parse(content.c_str()).HasParseError()) { std::cerr << "Error parsing \'PickupData.json\'!\n"; return; }

	for (auto& pickup : document["pickups"].GetArray())
	{
		PickupData data;
		data.m_durationInSecs	= pickup["duration"].GetFloat();
		data.m_effect			= m_effects[pickup["effect_id"].GetInt()];
		data.m_texture			= &m_sharedContext.m_textures.GetResource(pickup["texture"].GetString());

		m_pickupData[pickup["id"].GetInt()] = data;
	}
}

void PickupFactory::InitEffects()
{
	m_effects[0] = new HealthBoost(1.f);
	m_effects[1] = new SpeedBoost(5.f);
	m_effects[2] = new ShieldBoost(7.f);
}