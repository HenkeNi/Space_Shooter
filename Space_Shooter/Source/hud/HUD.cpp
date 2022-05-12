#include "pch.h"
#include "HUD.h"



//HUD::HUD(Player& aPlayer)
//	: m_player{ aPlayer }
//{
//}

void HUD::Init(SharedContext aSharedContext, Player* aPlayer)
{
	m_player = aPlayer;
	// READ from JSON (images -> extra lives)

	m_scoreLabel = std::make_unique<Label>(aSharedContext.m_window, "Score: ", aSharedContext.m_fonts.GetResource("fun_font"), 32);
	m_scoreLabel->SetPosition({ 75.f, 25.f});

	

	m_extraLives[0] = std::make_unique<Image>(aSharedContext.m_window, aSharedContext.m_textures.GetResource("ExtraLife"));
	m_extraLives[0]->SetPosition({ 75.f, 500.f });
	m_extraLives[1] = std::make_unique<Image>(aSharedContext.m_window, aSharedContext.m_textures.GetResource("ExtraLife"));
	m_extraLives[1]->SetPosition({ 125.f, 500.f });
	m_extraLives[2] = std::make_unique<Image>(aSharedContext.m_window, aSharedContext.m_textures.GetResource("ExtraLife"));
	m_extraLives[2]->SetPosition({ 175.f, 500.f });
}

void HUD::Recieve(const Event& aEvent)
{
	switch (aEvent.GetEventType())
	{
	case eEvent::PlayerHit:
		break;
	}
}

void HUD::HandleInput()
{
}

void HUD::Update(float aDeltaTime)
{
	//m_scoreLabel->SetText("Points: " + std::to_string(m_player.GetPoints()));
	m_scoreLabel->SetText("Points: 33");

	
	std::cout << m_player->GetLives() << '\n';
}

void HUD::Render(sf::RenderTarget& aTarget) const
{
	m_scoreLabel->Render();

	for (int i = 0; i < m_player->GetLives(); ++i)
	{
		m_extraLives[i]->Render();
	}
}