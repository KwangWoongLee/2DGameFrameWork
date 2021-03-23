#include "Game.h"

Game::Game()
    :mIsRunning(true)
    ,mWindow(nullptr)
{
}

bool Game::Init()
{
	// SDL 초기화
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// SDL 윈도우 생성
	mWindow = SDL_CreateWindow("2d Game Client", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	//SDL 렌더러 생성 , 수직동기화 및 그래픽 하드웨어 사용
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
    return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}



void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::UpdateGame()
{
	//프레임 제한 - 마지막 프레임 이후 델타시간이 목표보다 적을경우 해당 시간(16ms)까지 대기
	//실행환경이 달라 FPS가 달라지면 동작이 달라질 수 있기 때문에 사용
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;
	mTicksCount = SDL_GetTicks();

	//델타 최대 시간값을 고정
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	//TODO:델타 시간의 값으로 게임세계 업데이트

	
}

void Game::GenerateOutput()
{
	//후면버퍼(게임) 초기화
	//그리기 색상 지정
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	//현재 그리기 색상으로 초기화
	SDL_RenderClear(mRenderer);

	//TODO:그리기


	
	//전면버퍼(디스플레이)와 후면버퍼 교체
	SDL_RenderPresent(mRenderer);
}


void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}