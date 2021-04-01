#pragma once
#include "SDL.h"
#include "Input.h"
#include <vector>
#include <string>
#include <unordered_map>

class Game
{
public:
	Game(); 

	//���� �⺻ 3����
	//���� �ʱ�ȭ
	bool Init();
	//���� ���� ����
	void RunLoop();
	//���� ����
	void Shutdown();

	//���� ������ (��)�ε�
	void LoadData();
	void UnloadData();
	
	//Actor�߰� �� �����Լ�
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	//SpriteComponent �߰�, ����
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	//�̹��� ���Ͽ��� Texture�� ��ȯ
	SDL_Texture* GetTexture(const std::string& fileName);

	//tilemap ��������
	bool ReadTileMap(const std::string& fileName);
	void AddTile(class Tile* bomb);
	void RemoveTile(class Tile* bomb);
	std::vector<class Tile*>& GetTiles() { return mTiles; }

	void AddBomb(class Bomb* bomb);
	void RemoveBomb(class Bomb* bomb);
	std::vector<class Bomb*>& GetBombs() { return mBombs; }


private:
	//���� ���� ���� �Լ�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	//������Ʈ �Ϸ�� Actor vector
	std::vector<class Actor*> mActors;
	//������Ʈ �Ϸ���� ���� Actor vector;
	std::vector<class Actor*> mPendingActors;

	// SpriteComponent Vector // Game�� �׸��� ���� Sprite Vector
	std::vector<class SpriteComponent*> mSprites;

	// Texture map  <filename, SDL_Texture*> // Texture ��Ȱ���� ���� vector
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	//Ÿ�ϸ�
	std::vector<Tile*> mTiles;
	std::vector<std::vector<int>> mTileMapToInt;


	int	mMapSizeX;
	int mMapSizeY;

	//SDL ������
	SDL_Window*	mWindow;
	//SDL ������
	SDL_Renderer* mRenderer;
	//InputSystem
	Input* mInput;

	//���� ���� �Ǵ�
	bool		mIsRunning;
	//���� ƽ���� ������ ����
	Uint32		mTicksCount;
	//Actor ������Ʈ �Ϸ� Ȯ�� �Ǵ�
	bool		mIsUpdatingActors;
	


	std::vector<Bomb*> mBombs;
	

};

