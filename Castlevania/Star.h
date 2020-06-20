#pragma once
#include "Effect.h"
class Star :public Effect
{
public:
	Star() :Effect() {
		AddAnimation("START_ANI");
	}

	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
};

