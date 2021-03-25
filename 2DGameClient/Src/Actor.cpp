#include "Actor.h"
#include "Game.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mState(State::EActive)
	, mPosition(0.f,0.f)
{

}

Actor::~Actor()
{
	mGame->RemoveActor(this);
}

void Actor::Update(float deltaTime)
{
	UpdateActor(deltaTime);
}

void Actor::UpdateActor(float deltaTime)
{
	//virtual 가상함수, 실제 UpdateActor는 해당 Actor에서처리
	
}
