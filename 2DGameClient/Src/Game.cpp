#include "Game.h"
#include <algorithm>
#include "Actor.h"



Game::Game()
    :mIsRunning(true)
    ,mWindow(nullptr)
{
}

bool Game::Init()
{
	// SDL �ʱ�ȭ
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// SDL ������ ����
	mWindow = SDL_CreateWindow("2d Game Client", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	//SDL ������ ���� , ��������ȭ �� �׷��� �ϵ���� ���
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
    return true;
}


void Game::LoadData()
{
	//TODO : �پ��� ���͸� ����� �ε��غ���.
}

void Game::UnloadData()
{
	// actor �Ҹ��ڿ��� actor ��ü�� ��� ������ ������ ��츦 ���
	while (!mActors.empty())
	{
		delete mActors.back();
	}
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
	//������ ���� - ������ ������ ���� ��Ÿ�ð��� ��ǥ���� ������� �ش� �ð�(16ms)���� ���
	//����ȯ���� �޶� FPS�� �޶����� ������ �޶��� �� �ֱ� ������ ���
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;
	mTicksCount = SDL_GetTicks();

	//��Ÿ �ִ� �ð����� ����
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	//��Ÿ �ð��� ������ �̹� ������ ���Ӽ��� ������Ʈ
	mIsUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mIsUpdatingActors = false;

	//�̹� �����ӿ� ������Ʈ ���� ���� Actor���� mActors�� �߰�
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();


	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::State::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}


	for (auto actor : deadActors)
	{
		delete actor;
	}

	
}

void Game::GenerateOutput()
{
	//�ĸ����(����) �ʱ�ȭ
	//�׸��� ���� ����
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	//���� �׸��� �������� �ʱ�ȭ
	SDL_RenderClear(mRenderer);

	//TODO:�׸���


	
	//�������(���÷���)�� �ĸ���� ��ü
	SDL_RenderPresent(mRenderer);
}


void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	//Actor ������Ʈ ���̶��, �ӽ�Actor Vector�� Pending
	if (mIsUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	//actor ��ü�� delete�� ��, ~Actor()�� ���� ȣ��
	//actor pending vector�� ����actor vector ��ο� �ִٸ� �����ش�.  

	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		//TODO : swap �� pop_back�� ������ ? -> stl�����ϸ鼭 ã�ƺ���
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}


	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}
