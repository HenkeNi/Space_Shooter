#pragma once
#include "eCollisionLayer.h"
#include "Subscriber.h"


class CollisionObject;

class CollisionManager : public Subscriber
{
public:
	CollisionManager();
	~CollisionManager();

	void			Init();
	virtual void	Recieve(const Event& aEvent)	override;
	void			Update(float aDeltaTime);
	void			AddCollider(CollisionObject* aObject);
	void			RemoveCollider(CollisionObject* aObject);

private:
	/* - Methods - */
	void			CheckCollisions();
	// TODO: Resolve Collision?

	/* - Members - */
	std::vector<CollisionObject*> m_collisionObjects;  // Vector on Stack?? - circular delete?
};

