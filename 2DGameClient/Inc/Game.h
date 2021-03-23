#pragma once
#include "SDL.h"
#include <memory>

class Game
{
public:
	Game(); 

	//게임 초기화
	bool Init();
	//게임 루프 시작
	void RunLoop();
	//게임 종료
	void Shutdown();

private:
	//게임 루프 헬퍼 함수
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	//SDL 윈도우
	SDL_Window*	mWindow;
	//SDL 렌더러
	SDL_Renderer* mRenderer;

	//게임 실행 판단
	bool		mIsRunning;
	//현재 틱값을 갱신할 변수
	Uint32		mTicksCount;

};

