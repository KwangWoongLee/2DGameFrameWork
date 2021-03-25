#pragma once
#include "SDL.h"
#include <vector>

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

private:
	//게임 루프 헬퍼 함수
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	//업데이트 완료된 Actor vector
	std::vector<class Actor*> mActors;
	//업데이트 완료되지 않은 Actor vector;
	std::vector<class Actor*> mPendingActors;



	//SDL 윈도우
	SDL_Window*	mWindow;
	//SDL 렌더러
	SDL_Renderer* mRenderer;

	//게임 실행 판단
	bool		mIsRunning;
	//현재 틱값을 갱신할 변수
	Uint32		mTicksCount;
	//Actor 업데이트 완료 확인 판단
	bool		mIsUpdatingActors;
	



};

