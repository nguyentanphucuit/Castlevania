#pragma once
#include "Effect.h"
class Money700 :public Effect
{
public:
	Money700() :Effect() {
		AddAnimation("700_ANI");
	}

	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
};

