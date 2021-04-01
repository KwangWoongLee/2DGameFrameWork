#pragma once
#include "Actor.h"
#include "CollisionComponent.h"
class Bomb : public Actor
{
public:
	Bomb(class Game* game);
	~Bomb();

	void UpdateActor(float deltaTime) override;

	CollisionComponent* GetCollider() const { return mCollider; }



	bool	isFirstContact() const { return bFirstContact; }
	void	SetFirstContact() { bFirstContact = false; }

private:

	bool	isTimeToDeath();
	float	mDeathTimer;
	bool	bFirstContact;

	CollisionComponent* mCollider;
};

