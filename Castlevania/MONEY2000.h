#pragma once
#include "Effect.h"
class Money2000 :public Effect
{
public:
	Money2000() :Effect() {
		AddAnimation("2000_ANI");
	}

	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
};

