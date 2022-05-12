#pragma once
#include "Player.h"
#include "Subscriber.h"
#include "Image.h"
#include "Label.h"


#include "SharedContext.h"


class HUD : public Subscriber // Listen to player take hit... (or lose life)?
{
public:
	//HUD(Player& aPlayer);
	//HUD(int& somePlayerPoints);

	void			Init(SharedContext aSharedContext, Player* aPlayer);
	virtual void	Recieve(const Event& aEvent)	override;
	void			HandleInput();
	void			Update(float aDeltaTime);
	void			Render(sf::RenderTarget& aTarget)  const;

private:
	std::array<std::unique_ptr<Image>, 3>	m_extraLives;
	std::unique_ptr<Label>					m_scoreLabel;
	Player*									m_player;
	// Pointer to level? LevelManager?
};

