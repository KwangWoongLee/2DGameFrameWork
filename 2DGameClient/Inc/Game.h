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

	//게임 기본 3루프
	//게임 초기화
	bool Init();
	//게임 루프 시작
	void RunLoop();
	//게임 종료
	void Shutdown();

	//게임 데이터 (언)로드
	void LoadData();
	void UnloadData();
	
	//Actor추가 및 삭제함수
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	//SpriteComponent 추가, 삭제
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	//이미지 파일에서 Texture로 변환
	SDL_Texture* GetTexture(const std::string& fileName);

	//tilemap 가져오기
	bool ReadTileMap(const std::string& fileName);
	void AddTile(class Tile* bomb);
	void RemoveTile(class Tile* bomb);
	std::vector<class Tile*>& GetTiles() { return mTiles; }

	void AddBomb(class Bomb* bomb);
	void RemoveBomb(class Bomb* bomb);
	std::vector<class Bomb*>& GetBombs() { return mBombs; }


private:
	//게임 루프 헬퍼 함수
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	//업데이트 완료된 Actor vector
	std::vector<class Actor*> mActors;
	//업데이트 완료되지 않은 Actor vector;
	std::vector<class Actor*> mPendingActors;

	// SpriteComponent Vector // Game이 그리기 위한 Sprite Vector
	std::vector<class SpriteComponent*> mSprites;

	// Texture map  <filename, SDL_Texture*> // Texture 재활용을 위한 vector
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	//타일맵
	std::vector<Tile*> mTiles;
	std::vector<std::vector<int>> mTileMapToInt;


	int	mMapSizeX;
	int mMapSizeY;

	//SDL 윈도우
	SDL_Window*	mWindow;
	//SDL 렌더러
	SDL_Renderer* mRenderer;
	//InputSystem
	Input* mInput;

	//게임 실행 판단
	bool		mIsRunning;
	//현재 틱값을 갱신할 변수
	Uint32		mTicksCount;
	//Actor 업데이트 완료 확인 판단
	bool		mIsUpdatingActors;
	


	std::vector<Bomb*> mBombs;
	

};

