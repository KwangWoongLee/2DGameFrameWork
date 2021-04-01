#include "Game.h"
#include "Tile.h"
#include "TileMapComponent.h"

Tile::Tile(Game* game, int tilenum)
	: Actor(game)
	, mCollider(nullptr)
{
	TileMapComponent* tile = new TileMapComponent(this, 15);
	tile->SetSizeX(8);
	tile->SetSizeY(24);
	tile->SetTileNumber(tilenum);
	tile->SetTexture(game->GetTexture("Assets/Tiles.png"));

	CollisionComponent* collider = new CollisionComponent(this);
	collider->SetHalfHeight(32);
	collider->SetHalfWidth(32);

	mCollider = collider;
}

Tile::~Tile()
{
}

void Tile::UpdateActor(float deltaTime)
{

}
