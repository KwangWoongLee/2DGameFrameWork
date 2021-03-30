#include "Player.h"
#include "AnimationComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"

Player::Player(Game* game)
	:Actor(game)
{
	AnimationComponent* asc = new AnimationComponent(this);

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

	asc->SetAnimTexture(idle, 1);
	

	InputComponent* playerInputComponent = new InputComponent(this);
	playerInputComponent->SetMovingSpeed(30.f);

	playerInputComponent->SetForwardKey(SDL_SCANCODE_D);
	playerInputComponent->SetBackKey(SDL_SCANCODE_A);
	playerInputComponent->SetUpKey(SDL_SCANCODE_W);
	playerInputComponent->SetDownKey(SDL_SCANCODE_S);
}

void Player::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

}

void Player::ActorInput(const class KeyboardState& keyState)
{

}
