#pragma once
#include "SDL.h"
#include <vector>

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

private:
	//���� ���� ���� �Լ�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	//������Ʈ �Ϸ�� Actor vector
	std::vector<class Actor*> mActors;
	//������Ʈ �Ϸ���� ���� Actor vector;
	std::vector<class Actor*> mPendingActors;



	//SDL ������
	SDL_Window*	mWindow;
	//SDL ������
	SDL_Renderer* mRenderer;

	//���� ���� �Ǵ�
	bool		mIsRunning;
	//���� ƽ���� ������ ����
	Uint32		mTicksCount;
	//Actor ������Ʈ �Ϸ� Ȯ�� �Ǵ�
	bool		mIsUpdatingActors;
	



};

