#include "Game.h"
#include "Bomb.h"
#include "Boom.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"

Bomb::Bomb(Game* game)
	:Actor(game)
	,mCollider(nullptr)
	, mDeathTimer(0.f)
	, bFirstContact(true)
{
	AnimationComponent* anim = new AnimationComponent(this,150);
	SDL_Texture* bomb = game->GetTexture("Assets/bomb.bmp");

	anim->SetAnimTexture(bomb,4);

	CollisionComponent* collider = new CollisionComponent(this);
	collider->SetHalfHeight(anim->GetTextureHeight() * GetScale());
	collider->SetHalfWidth(anim->GetTextureWidth() / 4 * GetScale());

	mCollider = collider;

	game->AddBomb(this);

}

Bomb::~Bomb()
{
	GetGame()->RemoveBomb(this);
}

void Bomb::UpdateActor(float deltaTime)
{
	//Bomb Actor 의 자동 죽음처리
	mDeathTimer += deltaTime;
	if (isTimeToDeath())
	{
		SetState(Actor::State::EDead);
		Boom* boomCenter = new Boom(GetGame(),Boom::ECenter);
		boomCenter->SetPosition(GetPosition());

		Boom* boomRight = new Boom(GetGame(), Boom::ERight);
		boomRight->SetPosition(Vector2(GetPosition().x + 32, GetPosition().y));

		Boom* boomLeft = new Boom(GetGame(), Boom::ELeft);
		boomLeft->SetPosition(Vector2(GetPosition().x - 32, GetPosition().y));

		Boom* boomUp = new Boom(GetGame(), Boom::EUp);
		boomUp->SetPosition(Vector2(GetPosition().x, GetPosition().y-32));

		Boom* boomDown = new Boom(GetGame(), Boom::EDown);
		boomDown->SetPosition(Vector2(GetPosition().x, GetPosition().y + 32));
	}
}


bool Bomb::isTimeToDeath()
{
	return mDeathTimer >= 3.f;
}
