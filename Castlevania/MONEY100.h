#pragma once
#include "Effect.h"
class Money100 :public Effect
{
public:
	Money100() :Effect() {
		AddAnimation("100_ANI");
	}

	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
};

