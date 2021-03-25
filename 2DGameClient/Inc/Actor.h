#pragma once
#include <vector>
#include "Vector2.h"

class Actor
{
public:
	enum class State
	{
		EActive,
		EDead
	};

public:
	Actor(class Game* game);
	virtual ~Actor();

	//Game Update���� ȣ���ϴ� Update(UpdateGame -> �� Actor Update)
	void Update(float deltaTime);
	
	//Actor Update���� ȣ���ϴ� Update(Actor Update-> UpdateActor)
	virtual void UpdateActor(float deltaTime);

	//Getter , Setter
	State	GetState() const { return mState; }
	Vector2 GetPosition() const { return mPosition; }
	void	SetPosition(const Vector2& inPosition) { mPosition = inPosition; }

private:
	State	mState;
	Vector2 mPosition;

	//������ ����
	Game*	mGame;

};

