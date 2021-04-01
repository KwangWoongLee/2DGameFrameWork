#include "Game.h"
#include "Boom.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"

Boom::Boom(Game* game, BoomPosition state)
	:Actor(game)
	, mCollider(nullptr)
	, mDeathTimer(0.f)
	, EBoomPosition(state)
{
	AnimationComponent* anim = new AnimationComponent(this, 150);
	SDL_Texture* boomCenter = game->GetTexture("Assets/boom_center.bmp");
	SDL_Texture* boomLeft = game->GetTexture("Assets/boom_left.bmp");
	SDL_Texture* boomRight = game->GetTexture("Assets/boom_right.bmp");
	SDL_Texture* boomUp = game->GetTexture("Assets/boom_up.bmp");
	SDL_Texture* boomDown = game->GetTexture("Assets/boom_down.bmp");


	switch (EBoomPosition)
	{
	case ECenter:
		anim->SetAnimTexture(boomCenter,14);
		break;

	case ELeft:
		anim->SetAnimTexture(boomLeft, 9);
		break;

	case ERight:
		anim->SetAnimTexture(boomRight, 9);
		break;

	case EUp:
		anim->SetAnimTexture(boomUp, 9);
		break;

	case EDown:
		anim->SetAnimTexture(boomDown, 9);
		break;
	}

	CollisionComponent* collider = new CollisionComponent(this);
	collider->SetHalfHeight(anim->GetTextureHeight() * GetScale());
	collider->SetHalfWidth(anim->GetTextureWidth() / 4 * GetScale());

	mCollider = collider;


}

Boom::~Boom()
{
}

void Boom::UpdateActor(float deltaTime)
{
	//Boom Actor 의 자동 죽음처리
	mDeathTimer += deltaTime;
	if (isTimeToDeath())
		SetState(Actor::State::EDead);

}


bool Boom::isTimeToDeath()
{
	return mDeathTimer >= 0.8f;
}
