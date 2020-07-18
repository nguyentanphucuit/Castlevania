#pragma once
#include "Effect.h"
class Money1000 :public Effect
{
public:
	Money1000() :Effect() {
		AddAnimation("1000_ANI");
	}

	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
};

