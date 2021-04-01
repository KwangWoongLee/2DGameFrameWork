#pragma once
#include "Actor.h"
#include "CollisionComponent.h"

class Tile : public Actor
{
public:
	Tile(class Game* game, int tilenum);
	~Tile();

	void UpdateActor(float deltaTime) override;

	CollisionComponent* GetCollider() const { return mCollider; }

private:
	CollisionComponent* mCollider;
};

