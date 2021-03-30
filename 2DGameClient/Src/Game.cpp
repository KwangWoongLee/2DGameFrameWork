#include "Game.h"
#include "Input.h"
#include <algorithm>
#include "Actor.h"
#include "Player.h"
#include <SDL_image.h>
#include "SpriteComponent.h"



Game::Game()
    :mIsRunning(true)
    ,mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsUpdatingActors(false)
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
	mWindow = SDL_CreateWindow("2d Game Client", 30, 30, 1024, 768, 0);
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

	//PNG�� �����ϴ� SDL Image �ʱ�ȭ
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	mInput = new Input();
	if (!mInput->Init())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();

    return true;
}


void Game::LoadData()
{
	//TODO : �پ��� ���͸� ����� �� ���Ϳ� ������Ʈ�� �߰��غ���.
	Actor* bgActor = new Actor(this);
	bgActor->SetPosition(Vector2(512.f, 384.f));
	
	SpriteComponent* bgComponent = new SpriteComponent(bgActor, 10);

	bgComponent->SetTexture(GetTexture("Assets/bg.png"));

	Player* p = new Player(this);
	p->SetPosition(Vector2(100.0f, 384.0f));
	p->SetScale(1.5f);



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
	mInput->PrepareForUpdate();

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

	KeyboardState keyState = mInput->GetKeyboardState();

	if (keyState.GetKeyState(SDL_SCANCODE_ESCAPE)
		== EReleased)
	{
		mIsRunning = false;
	}


	mIsUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
	mIsUpdatingActors = false;
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
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	
	//�������(���÷���)�� �ĸ���� ��ü
	SDL_RenderPresent(mRenderer);
}


void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
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

void Game::AddSprite(SpriteComponent* sprite)
{
	//�׸��� ������ ���� sprite vector�� �ڵ�����
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;

	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		//texture ��Ȱ��
		tex = iter->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		//�÷�Ű ����
		SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 255, 0, 255));


		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}
