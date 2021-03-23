#pragma once
#include "SDL.h"
#include <memory>

class Game
{
public:
	Game(); 

	//���� �ʱ�ȭ
	bool Init();
	//���� ���� ����
	void RunLoop();
	//���� ����
	void Shutdown();

private:
	//���� ���� ���� �Լ�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	//SDL ������
	SDL_Window*	mWindow;
	//SDL ������
	SDL_Renderer* mRenderer;

	//���� ���� �Ǵ�
	bool		mIsRunning;
	//���� ƽ���� ������ ����
	Uint32		mTicksCount;

};

