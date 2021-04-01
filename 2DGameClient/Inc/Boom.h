#pragma once
#include "Actor.h"
#include "CollisionComponent.h"
class Boom : public Actor
{
public:
	enum BoomPosition
	{
		ECenter,
		ELeft,
		ERight,
		EUp,
		EDown
	} EBoomPosition;

	Boom(class Game* game, BoomPosition state);
	~Boom();

	void UpdateActor(float deltaTime) override;

	CollisionComponent* GetCollider() const { return mCollider; }


private:
	bool	isTimeToDeath();
	float	mDeathTimer;

	CollisionComponent* mCollider;
};

