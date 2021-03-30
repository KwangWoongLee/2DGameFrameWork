#pragma once
#include "Actor.h"
#include "Game.h"
#include "MoveComponent.h"

class Player : public Actor
{
public:

	Player(class Game* game);
	virtual void UpdateActor(float deltaTime) override;
	
	void ActorInput(const class KeyboardState& keyState) override;



private:
	
};

