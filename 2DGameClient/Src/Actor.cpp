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
	//virtual �����Լ�, ���� UpdateActor�� �ش� Actor����ó��
	
}
