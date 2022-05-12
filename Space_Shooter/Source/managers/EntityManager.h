#pragma once
#include "Entity.h"
#include "Subscriber.h"

class EntityManager : public Subscriber
{
public:
	EntityManager(sf::RenderWindow& aWindow);
	~EntityManager();

	virtual void	Recieve(const Event& aEvent)				override;
	void			Update(float aDeltaTime);
	void			Render(sf::RenderTarget& aTarget)			   const;

	void			AddEntity(Entity* aEntity);
	void			RemoveEntity(const unsigned int aID);
	void			Clear();
	void			Init();

private:
	/* - Methods - */
	void			SetupSubscriptions();
	void			CancelSubscriptions();
	void			UpdateEntities(float aDeltaTime);
	bool			IsOutOfBounds(Entity& aEntity);

	/* - Members - */
	std::vector<Entity*> m_entities; // use vector on stack instead!?
	sf::RenderWindow&	 m_window;
};

