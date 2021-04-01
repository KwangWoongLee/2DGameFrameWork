#include "Player.h"
#include "AnimationComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "CollisionComponent.h"
#include "Bomb.h"
#include "Tile.h"

Player::Player(Game* game)
	:Actor(game)
{
	SetScale(0.7f);

	AnimationComponent* asc = new AnimationComponent(this,200);

	SDL_Texture* idle = game->GetTexture("Assets/idle.bmp");
	SDL_Texture* down = game->GetTexture("Assets/down.bmp");
	SDL_Texture* left = game->GetTexture("Assets/left.bmp");
	SDL_Texture* right = game->GetTexture("Assets/right.bmp");
	SDL_Texture* up = game->GetTexture("Assets/up.bmp");

	asc->AddAnimTextures("idle", idle);
	asc->AddAnimTextures("down", down);
	asc->AddAnimTextures("left", left);
	asc->AddAnimTextures("right", right);
	asc->AddAnimTextures("up", up);

	asc->SetAnimTexture(down, 8);
	SetMovingState(Actor::MovingState::EIdle);


	InputComponent* playerInputComponent = new InputComponent(this);
	playerInputComponent->SetMovingSpeed(30.f);

	playerInputComponent->SetForwardKey(SDL_SCANCODE_D);
	playerInputComponent->SetBackKey(SDL_SCANCODE_A);
	playerInputComponent->SetUpKey(SDL_SCANCODE_W);
	playerInputComponent->SetDownKey(SDL_SCANCODE_S);

	CollisionComponent* collider = new CollisionComponent(this);
	collider->SetHalfHeight(asc->GetTextureHeight() * GetScale());
	collider->SetHalfWidth(asc->GetTextureWidth()/8 * GetScale());
	
	mCollider = collider;

}

void Player::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	for (auto tile : GetGame()->GetTiles())
	{
		float CollisionX, CollisionY;
		//폭탄과 충돌했다면,
		if (Intersect(*GetCollider(), *(tile->GetCollider()), &CollisionX, &CollisionY))
		{
			if (GetMovingState() == Actor::MovingState::ERight)
			{
				Vector2 pos = GetPosition();
				pos.x -= CollisionX;
				SetPosition(pos);
			}
			else if (GetMovingState() == Actor::MovingState::ELeft)
			{
				Vector2 pos = GetPosition();
				pos.x += CollisionX;
				SetPosition(pos);
			}
			else if (GetMovingState() == Actor::MovingState::EUp)
			{
				Vector2 pos = GetPosition();
				pos.y += CollisionY;
				SetPosition(pos);
			}
			else if (GetMovingState() == Actor::MovingState::EDown)
			{
				Vector2 pos = GetPosition();
				pos.y -= CollisionY;
				SetPosition(pos);
			}
			break;
		}
	}

	for (auto bomb : GetGame()->GetBombs())
	{
		float CollisionX, CollisionY;
		//폭탄과 충돌했다면,
		if (Intersect(*GetCollider(), *(bomb->GetCollider()), &CollisionX, &CollisionY))
		{
			//폭탄을 처음 놓을 때는 충돌처리 하지 않음
			if (bomb->isFirstContact())
			{
				continue;
			}

			if (GetMovingState() == Actor::MovingState::ERight)
			{
				Vector2 pos = GetPosition();
				pos.x -= CollisionX;
				SetPosition(pos);
			}
			else if (GetMovingState() == Actor::MovingState::ELeft)
			{
				Vector2 pos = GetPosition();
				pos.x += CollisionX;
				SetPosition(pos);
			}
			else if (GetMovingState() == Actor::MovingState::EUp)
			{
				Vector2 pos = GetPosition();
				pos.y += CollisionY;
				SetPosition(pos);
			}
			else if (GetMovingState() == Actor::MovingState::EDown)
			{
				Vector2 pos = GetPosition();
				pos.y -= CollisionY;
				SetPosition(pos);
			}
			break;
		}
		//충돌하지 않았을 때,
		else
		{
			
			bomb->SetFirstContact();
		}

	}
	

}

void Player::ActorInput(const class KeyboardState& keyState)
{
	if (keyState.GetKeyValue(SDL_SCANCODE_SPACE))
	{	
		Vector2 pos = SearchBombPosition(GetPosition());
		for (auto bomb : GetGame()->GetBombs())
		{
			if (pos.x == bomb->GetPosition().x && pos.y == bomb->GetPosition().y)
				return;
		}

		Bomb* bomb = new Bomb(GetGame());
		bomb->SetPosition(pos);
	}
}

Vector2 Player::SearchBombPosition(const Vector2& ownerPos)
{
	int x = static_cast<int>(fabsf(ownerPos.x) / 32) * 32 + 16;
	int y = static_cast<int>(fabsf(ownerPos.y) / 32) * 32 + 16;

	return Vector2(x, y);
}
