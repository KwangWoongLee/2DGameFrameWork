#pragma once
#include "Actor.h"
#include "Game.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"

class Player : public Actor
{
public:

	Player(class Game* game);
	virtual void UpdateActor(float deltaTime) override;
	
	void ActorInput(const class KeyboardState& keyState) override;

	Vector2 SearchBombPosition(const Vector2& ownerPos);

	CollisionComponent* GetCollider() const { return mCollider; }

private:
	CollisionComponent* mCollider;
};

